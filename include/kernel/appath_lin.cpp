
#if defined(_DVN_LIN_)

#include <kernel/constdef.h>

namespace dvnci {

    const std::string DVNCI_NIX_CONFIG_DIR = "/home/sealeks/";
    const std::string DVNCI_NIX_CONFIG_FILE = "base.ini";
    const std::string DVNCI_NIX_CONFIG_FULL = DVNCI_NIX_CONFIG_DIR + DVNCI_NIX_CONFIG_FILE;

    fspath getlocalbasepath() {
        if (boost::filesystem::exists(DVNCI_NIX_CONFIG_FULL.c_str())) {
            std::ifstream ifs(DVNCI_NIX_CONFIG_FULL.c_str());
            if (!ifs)
                return "";
            std::string tmpstr = "";
            ifs >> tmpstr;
            return tmpstr.c_str();
        }
        return "";
    }

    fspath setlocalbasepath(const fspath& path) {
        {
            boost::system::error_code ec;
            if (!boost::filesystem::exists(DVNCI_NIX_CONFIG_DIR.c_str())) {
                if (!boost::filesystem::create_directories(DVNCI_NIX_CONFIG_DIR.c_str(), ec)) {
                    DEBUG_VAL_DVNCI(ec.message())
                    return "";
                }
                if (ec) {
                    DEBUG_VAL_DVNCI(ec.message())
                    return "";
                }
            }

            std::ofstream ofs(DVNCI_NIX_CONFIG_FULL.c_str(), std::ofstream::trunc);
            ofs << path.string();
        }
        return getlocalbasepath();
    }


}

#endif



