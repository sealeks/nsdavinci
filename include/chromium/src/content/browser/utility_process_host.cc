// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "content/browser/utility_process_host.h"

#include "base/command_line.h"
#include "base/message_loop.h"
#include "content/browser/content_browser_client.h"
#include "content/common/content_switches.h"
#include "content/common/utility_messages.h"
#include "ipc/ipc_switches.h"
#include "ui/base/ui_base_switches.h"

UtilityProcessHost::Client::Client() {
}

UtilityProcessHost::Client::~Client() {
}

void UtilityProcessHost::Client::OnProcessCrashed(int exit_code) {
}

bool UtilityProcessHost::Client::OnMessageReceived(
    const IPC::Message& message) {
  return false;
}

UtilityProcessHost::UtilityProcessHost(Client* client,
                                       BrowserThread::ID client_thread_id)
    : BrowserChildProcessHost(UTILITY_PROCESS),
      client_(client),
      client_thread_id_(client_thread_id),
      is_batch_mode_(false),
      started_(false) {
}

UtilityProcessHost::~UtilityProcessHost() {
  DCHECK(!is_batch_mode_);
}

bool UtilityProcessHost::Send(IPC::Message* message) {
  if (!StartProcess())
    return false;

  return BrowserChildProcessHost::Send(message);
}

bool UtilityProcessHost::StartBatchMode()  {
  CHECK(!is_batch_mode_);
  is_batch_mode_ = StartProcess();
  Send(new UtilityMsg_BatchMode_Started());
  return is_batch_mode_;
}

void UtilityProcessHost::EndBatchMode()  {
  CHECK(is_batch_mode_);
  is_batch_mode_ = false;
  Send(new UtilityMsg_BatchMode_Finished());
}

FilePath UtilityProcessHost::GetUtilityProcessCmd() {
  return GetChildPath(true);
}

bool UtilityProcessHost::StartProcess() {
  if (started_)
    return true;
  started_ = true;

  if (is_batch_mode_)
    return true;
  // Name must be set or metrics_service will crash in any test which
  // launches a UtilityProcessHost.
  set_name(L"utility process");

  if (!CreateChannel())
    return false;

  FilePath exe_path = GetUtilityProcessCmd();
  if (exe_path.empty()) {
    NOTREACHED() << "Unable to get utility process binary name.";
    return false;
  }

  CommandLine* cmd_line = new CommandLine(exe_path);
  cmd_line->AppendSwitchASCII(switches::kProcessType,
                              switches::kUtilityProcess);
  cmd_line->AppendSwitchASCII(switches::kProcessChannelID, channel_id());
  std::string locale =
      content::GetContentClient()->browser()->GetApplicationLocale();
  cmd_line->AppendSwitchASCII(switches::kLang, locale);

  const CommandLine& browser_command_line = *CommandLine::ForCurrentProcess();
  if (browser_command_line.HasSwitch(switches::kChromeFrame))
    cmd_line->AppendSwitch(switches::kChromeFrame);
  if (browser_command_line.HasSwitch(switches::kNoSandbox))
    cmd_line->AppendSwitch(switches::kNoSandbox);

#if defined(OS_POSIX)
  // TODO(port): Sandbox this on Linux.  Also, zygote this to work with
  // Linux updating.
  bool has_cmd_prefix = browser_command_line.HasSwitch(
      switches::kUtilityCmdPrefix);
  if (has_cmd_prefix) {
    // launch the utility child process with some prefix (usually "xterm -e gdb
    // --args").
    cmd_line->PrependWrapper(browser_command_line.GetSwitchValueNative(
        switches::kUtilityCmdPrefix));
  }

  cmd_line->AppendSwitchPath(switches::kUtilityProcessAllowedDir, exposed_dir_);
#endif

  Launch(
#if defined(OS_WIN)
      exposed_dir_,
#elif defined(OS_POSIX)
      false,
      base::environment_vector(),
#endif
      cmd_line);

  return true;
}

bool UtilityProcessHost::OnMessageReceived(const IPC::Message& message) {
  BrowserThread::PostTask(
      client_thread_id_, FROM_HERE,
      NewRunnableMethod(client_.get(), &Client::OnMessageReceived, message));
  return true;
}

void UtilityProcessHost::OnProcessCrashed(int exit_code) {
  BrowserThread::PostTask(
      client_thread_id_, FROM_HERE,
      NewRunnableMethod(client_.get(), &Client::OnProcessCrashed, exit_code));
}

bool UtilityProcessHost::CanShutdown() {
  return true;
}
