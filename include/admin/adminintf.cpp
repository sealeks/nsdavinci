/* 
 * File:   kernelInterface.cpp
 * Author: Serg Alexeev sealeks@mail.ru
 * 
 * Created on 21 Декабрь 2009 г., 11:46
 */

#include <admin/adminintf.h>

namespace dvnci {
    namespace admin {

        using namespace std;

        iteminfo_map & operator<<(iteminfo_map& ls, const resp_entitysigs& rs) {
            for (vect_entitysig_data::const_iterator it = rs.sigs.begin(); it != rs.sigs.end(); ++it) {
                ls.insert(iteminfo_pair(static_cast<indx> (it->key),
                        name_with_type(it->name, nodeinfotype(it->tpitem))));
            }
            return ls;
        }

        req_tags & operator<<(req_tags& rs, const indx_set& ls) {
            ls >> rs.keys;
            return rs;
        }

        indx_tags_map & operator<<(indx_tags_map& ls, const resp_tags& rs) {
            for (vect_tag_data::const_iterator it = rs.tags.begin(); it != rs.tags.end(); ++it) {
                if (ls.find(static_cast<indx> (it->key)) != ls.end())
                    ls[static_cast<indx> (it->key)] = *it;
                else
                    ls.insert(indx_tags_pair(static_cast<indx> (it->key), *it));
            }
            return ls;
        }

        indx_tags_map & operator<<(indx_tags_map& ls, const resp_sendtags& rs) {
            for (vect_tag_data::const_iterator it = rs.tags.begin(); it != rs.tags.end(); ++it) {
                if (ls.find(static_cast<indx> (it->key)) != ls.end())
                    ls[static_cast<indx> (it->key)] = *it;
                else
                    ls.insert(indx_tags_pair(static_cast<indx> (it->key), *it));
            }
            return ls;
        }

        req_groups & operator<<(req_groups& rs, const indx_set& ls) {
            ls >> rs.keys;
            return rs;
        }

        indx_groups_map & operator<<(indx_groups_map& ls, const resp_groups& rs) {
            for (vect_group_data::const_iterator it = rs.groups.begin(); it != rs.groups.end(); ++it) {
                if (ls.find(static_cast<indx> (it->key)) != ls.end())
                    ls[static_cast<indx> (it->key)] = *it;
                else
                    ls.insert(indx_groups_pair(static_cast<indx> (it->key), *it));
            }
            return ls;
        }

        indx_groups_map & operator<<(indx_groups_map& ls, const resp_sendgroups& rs) {
            for (vect_group_data::const_iterator it = rs.groups.begin(); it != rs.groups.end(); ++it) {
                if (ls.find(static_cast<indx> (it->key)) != ls.end())
                    ls[static_cast<indx> (it->key)] = *it;
                else
                    ls.insert(indx_groups_pair(static_cast<indx> (it->key), *it));
            }
            return ls;
        }

        req_agroups & operator<<(req_agroups& rs, const indx_set& ls) {
            ls >> rs.keys;
            return rs;
        }

        indx_agroups_map & operator<<(indx_agroups_map& ls, const resp_agroups& rs) {
            for (vect_agroup_data::const_iterator it = rs.agroups.begin(); it != rs.agroups.end(); ++it) {
                if (ls.find(static_cast<indx> (it->key)) != ls.end())
                    ls[static_cast<indx> (it->key)] = *it;
                else
                    ls.insert(indx_agroups_pair(static_cast<indx> (it->key), *it));
            }
            return ls;
        }

        indx_agroups_map & operator<<(indx_agroups_map& ls, const resp_sendagroups& rs) {
            for (vect_agroup_data::const_iterator it = rs.agroups.begin(); it != rs.agroups.end(); ++it) {
                if (ls.find(static_cast<indx> (it->key)) != ls.end())
                    ls[static_cast<indx> (it->key)] = *it;
                else
                    ls.insert(indx_agroups_pair(static_cast<indx> (it->key), *it));
            }
            return ls;
        }

        req_accessrules & operator<<(req_accessrules& rs, const indx_set& ls) {
            ls >> rs.keys;
            return rs;
        }

        indx_accessrules_map & operator<<(indx_accessrules_map& ls, const resp_accessrules& rs) {
            for (vect_accessrule_data::const_iterator it = rs.accessrules.begin(); it != rs.accessrules.end(); ++it) {
                if (ls.find(static_cast<indx> (it->key)) != ls.end())
                    ls[static_cast<indx> (it->key)] = *it;
                else
                    ls.insert(indx_accessrules_pair(static_cast<indx> (it->key), *it));
            }
            return ls;
        }

        indx_accessrules_map & operator<<(indx_accessrules_map& ls, const resp_sendaccessrules& rs) {
            for (vect_accessrule_data::const_iterator it = rs.accessrules.begin(); it != rs.accessrules.end(); ++it) {
                if (ls.find(static_cast<indx> (it->key)) != ls.end())
                    ls[static_cast<indx> (it->key)] = *it;
                else
                    ls.insert(indx_accessrules_pair(static_cast<indx> (it->key), *it));
            }
            return ls;
        }

        req_users & operator<<(req_users& rs, const indx_set& ls) {
            ls >> rs.keys;
            return rs;
        }

        indx_users_map & operator<<(indx_users_map& ls, const resp_users& rs) {
            for (vect_user_data::const_iterator it = rs.users.begin(); it != rs.users.end(); ++it) {
                if (ls.find(static_cast<indx> (it->key)) != ls.end())
                    ls[static_cast<indx> (it->key)] = *it;
                else
                    ls.insert(indx_users_pair(static_cast<indx> (it->key), *it));
            }
            return ls;
        }

        indx_users_map & operator<<(indx_users_map& ls, const resp_sendusers& rs) {
            for (vect_user_data::const_iterator it = rs.users.begin(); it != rs.users.end(); ++it) {
                if (ls.find(static_cast<indx> (it->key)) != ls.end())
                    ls[static_cast<indx> (it->key)] = *it;
                else
                    ls.insert(indx_users_pair(static_cast<indx> (it->key), *it));
            }
            return ls;
        }

        req_services & operator<<(req_services& rs, const indx_set& ls) {

            ls >> rs.keys;
            return rs;
        }

        indx_services_map & operator<<(indx_services_map& ls, const resp_services& rs) {
            for (vect_service_data::const_iterator it = rs.services.begin(); it != rs.services.end(); ++it) {
                if (ls.find(static_cast<indx> (it->key)) != ls.end())
                    ls[static_cast<indx> (it->key)] = *it;
                else
                    ls.insert(indx_services_pair(static_cast<indx> (it->key), *it));
            }
            return ls;
        }

        indx_services_map & operator<<(indx_services_map& ls, const resp_sendservices& rs) {
            for (vect_service_data::const_iterator it = rs.services.begin(); it != rs.services.end(); ++it) {
                if (ls.find(static_cast<indx> (it->key)) != ls.end())
                    ls[static_cast<indx> (it->key)] = *it;
                else
                    ls.insert(indx_services_pair(static_cast<indx> (it->key), *it));
            }
            return ls;
        }

        req_metas & operator<<(req_metas& rs, const indx_set& ls) {
            ls >> rs.keys;
            return rs;
        }

        req_config & operator<<(req_config& rs, const indx_set& ls) {
            return rs;
        }

        ////////////////////////////////////////////////////////////////////

        metaintf::metaintf() {
            propertymeta_ids.insert(propertymeta_ids_pair(PROPERTY_MF_name, 0));
            propertymeta_ids.insert(propertymeta_ids_pair(PROPERTY_MF_color, 1));
            propertymeta_ids.insert(propertymeta_ids_pair(PROPERTY_MF_textcolor, 2));
            propertymeta_ids.insert(propertymeta_ids_pair(PROPERTY_MF_fontsize, 3));
            propertymeta_ids.insert(propertymeta_ids_pair(PROPERTY_MF_delt, 4));
            propertymeta_ids.insert(propertymeta_ids_pair(PROPERTY_MF_group, 5));
            propertymeta_ids.insert(propertymeta_ids_pair(PROPERTY_MF_width, 6));
            propertymeta_ids.insert(propertymeta_ids_pair(PROPERTY_MF_height, 7));
            propertymeta_ids.insert(propertymeta_ids_pair(PROPERTY_MF_type, 8));
            propertymeta_ids.insert(propertymeta_ids_pair(PROPERTY_MF_initperiod, 9));
            propertymeta_ids.insert(propertymeta_ids_pair(PROPERTY_MF_subperiod, 10));
            propertymeta_ids.insert(propertymeta_ids_pair(PROPERTY_MF_autoprint, 11));
            propertymeta_ids.insert(propertymeta_ids_pair(PROPERTY_MF_autoclose, 12));
            propertymeta_ids.insert(propertymeta_ids_pair(PROPERTY_MF_foottext, 13));
            propertymeta_ids.insert(propertymeta_ids_pair(PROPERTY_MF_tg, 0));
            propertymeta_ids.insert(propertymeta_ids_pair(PROPERTY_MF_sumtype, 9));
            propertymeta_ids.insert(propertymeta_ids_pair(PROPERTY_MF_round, 10));
            propertymeta_ids.insert(propertymeta_ids_pair(PROPERTY_MF_rowcolor, 11));
            propertymeta_ids.insert(propertymeta_ids_pair(PROPERTY_MF_negcolor, 12));
            propertymeta_ids.insert(propertymeta_ids_pair(PROPERTY_MF_fill, 13));
            propertymeta_ids.insert(propertymeta_ids_pair(PROPERTY_MF_pencolor, 14));
            propertymeta_ids.insert(propertymeta_ids_pair(PROPERTY_MF_fillcolor, 15));
            propertymeta_ids.insert(propertymeta_ids_pair(PROPERTY_MF_DBProvider, 0));
            propertymeta_ids.insert(propertymeta_ids_pair(PROPERTY_MF_constring, 1));
            propertymeta_ids.insert(propertymeta_ids_pair(PROPERTY_MF_host, 2));

            propertymeta_ids_map NT_MF_REPHEADER_tmpmap;
            NT_MF_REPHEADER_tmpmap.insert(*propertymeta_ids.find(PROPERTY_MF_name));
            NT_MF_REPHEADER_tmpmap.insert(*propertymeta_ids.find(PROPERTY_MF_color));
            NT_MF_REPHEADER_tmpmap.insert(*propertymeta_ids.find(PROPERTY_MF_textcolor));
            NT_MF_REPHEADER_tmpmap.insert(*propertymeta_ids.find(PROPERTY_MF_fontsize));
            metaidsmap_map.insert(nodetype_metaidsmap_pair(NT_MF_REPHEADER, NT_MF_REPHEADER_tmpmap));

            propertymeta_ids_map NT_MF_REPARR_tmpmap;
            NT_MF_REPARR_tmpmap.insert(*propertymeta_ids.find(PROPERTY_MF_name));
            NT_MF_REPARR_tmpmap.insert(*propertymeta_ids.find(PROPERTY_MF_delt));
            NT_MF_REPARR_tmpmap.insert(*propertymeta_ids.find(PROPERTY_MF_group));
            NT_MF_REPARR_tmpmap.insert(*propertymeta_ids.find(PROPERTY_MF_width));
            NT_MF_REPARR_tmpmap.insert(*propertymeta_ids.find(PROPERTY_MF_height));
            NT_MF_REPARR_tmpmap.insert(*propertymeta_ids.find(PROPERTY_MF_type));
            NT_MF_REPARR_tmpmap.insert(*propertymeta_ids.find(PROPERTY_MF_initperiod));
            NT_MF_REPARR_tmpmap.insert(*propertymeta_ids.find(PROPERTY_MF_subperiod));
            NT_MF_REPARR_tmpmap.insert(*propertymeta_ids.find(PROPERTY_MF_autoprint));
            NT_MF_REPARR_tmpmap.insert(*propertymeta_ids.find(PROPERTY_MF_autoclose));
            NT_MF_REPARR_tmpmap.insert(*propertymeta_ids.find(PROPERTY_MF_foottext));
            metaidsmap_map.insert(nodetype_metaidsmap_pair(NT_MF_REPARR, NT_MF_REPARR_tmpmap));

            propertymeta_ids_map NT_MF_UNIT_tmpmap;
            NT_MF_UNIT_tmpmap.insert(*propertymeta_ids.find(PROPERTY_MF_tg));
            NT_MF_UNIT_tmpmap.insert(*propertymeta_ids.find(PROPERTY_MF_sumtype));
            NT_MF_UNIT_tmpmap.insert(*propertymeta_ids.find(PROPERTY_MF_round));
            NT_MF_UNIT_tmpmap.insert(*propertymeta_ids.find(PROPERTY_MF_rowcolor));
            NT_MF_UNIT_tmpmap.insert(*propertymeta_ids.find(PROPERTY_MF_textcolor));
            NT_MF_UNIT_tmpmap.insert(*propertymeta_ids.find(PROPERTY_MF_negcolor));
            metaidsmap_map.insert(nodetype_metaidsmap_pair(NT_MF_UNIT, NT_MF_UNIT_tmpmap));

            propertymeta_ids_map NT_MF_TRENDHEADER_tmpmap;
            NT_MF_TRENDHEADER_tmpmap.insert(*propertymeta_ids.find(PROPERTY_MF_name));
            metaidsmap_map.insert(nodetype_metaidsmap_pair(NT_MF_TRENDHEADER, NT_MF_TRENDHEADER_tmpmap));

            propertymeta_ids_map NT_MF_TRENDARR_tmpmap;
            NT_MF_TRENDARR_tmpmap.insert(*propertymeta_ids.find(PROPERTY_MF_name));
            metaidsmap_map.insert(nodetype_metaidsmap_pair(NT_MF_TRENDARR, NT_MF_TRENDARR_tmpmap));

            propertymeta_ids_map NT_MF_TREND_tmpmap;
            NT_MF_TREND_tmpmap.insert(*propertymeta_ids.find(PROPERTY_MF_tg));
            NT_MF_TREND_tmpmap.insert(*propertymeta_ids.find(PROPERTY_MF_width));
            NT_MF_TREND_tmpmap.insert(*propertymeta_ids.find(PROPERTY_MF_height));
            NT_MF_TREND_tmpmap.insert(*propertymeta_ids.find(PROPERTY_MF_fill));
            NT_MF_TREND_tmpmap.insert(*propertymeta_ids.find(PROPERTY_MF_pencolor));
            NT_MF_TREND_tmpmap.insert(*propertymeta_ids.find(PROPERTY_MF_fillcolor));
            metaidsmap_map.insert(nodetype_metaidsmap_pair(NT_MF_TREND, NT_MF_TREND_tmpmap));

            propertymeta_ids_map NT_MF_MESSHEADER_tmpmap;
            NT_MF_MESSHEADER_tmpmap.insert(*propertymeta_ids.find(PROPERTY_MF_name));
            metaidsmap_map.insert(nodetype_metaidsmap_pair(NT_MF_MESSHEADER, NT_MF_MESSHEADER_tmpmap));

            propertymeta_ids_map NT_MF_MESSARR_tmpmap;
            NT_MF_MESSARR_tmpmap.insert(*propertymeta_ids.find(PROPERTY_MF_name));
            metaidsmap_map.insert(nodetype_metaidsmap_pair(NT_MF_MESSARR, NT_MF_MESSARR_tmpmap));

            propertymeta_ids_map NT_MF_MESSAGE_tmpmap;
            NT_MF_MESSAGE_tmpmap.insert(*propertymeta_ids.find(PROPERTY_MF_tg));
            metaidsmap_map.insert(nodetype_metaidsmap_pair(NT_MF_MESSAGE, NT_MF_MESSAGE_tmpmap));

            propertymeta_ids_map NT_MF_META_tmpmap;
            NT_MF_META_tmpmap.insert(*propertymeta_ids.find(PROPERTY_MF_DBProvider));
            NT_MF_META_tmpmap.insert(*propertymeta_ids.find(PROPERTY_MF_constring));
            NT_MF_META_tmpmap.insert(*propertymeta_ids.find(PROPERTY_MF_host));
            metaidsmap_map.insert(nodetype_metaidsmap_pair(NT_MF_ROOT, NT_MF_META_tmpmap));
        };

        ////////////////////////////////////////////////////////////////////

        ns_error adminintf::read_view(nodetype ittp, const std::string& strcriteria) {

            THD_EXCLUSIVE_LOCK(mutex);
            switch (ittp) {
                case NT_REGISTRY:
                {
                    regs_mf(strcriteria);
                    break;
                };
                case NT_ALARM:
                {
                    alarms_mf(strcriteria);
                    break;
                };
                case NT_CLIENT:
                {
                    clients_mf(strcriteria);
                    break;
                };
                case NT_COMMAND:
                {
                    commands_mf(strcriteria);
                    break;
                };
                case NT_LOG:
                {
                    debug_mf(strcriteria);
                    break;
                };
                case NT_JOURNAL:
                {
                    journal_mf(strcriteria);
                    break;
                };
            }
            return NS_ERROR_SUCCESS;
        };

        adminintf::adminintf() : locale_(0), isautorizated_(false) {
            config_map.insert(confinfo_pair(NS_CNFG_ROOT, 0));
            config_map.insert(confinfo_pair(NS_CNFG_PATH, 1));
            config_map.insert(confinfo_pair(NS_CNFG_NAME, 2));
            config_map.insert(confinfo_pair(NS_CNFG_COMMENT, 3));
            config_map.insert(confinfo_pair(NS_CNFG_ARCHCNT, 4));
            config_map.insert(confinfo_pair(NS_CNFG_MAPSZ, 5));
            config_map.insert(confinfo_pair(NS_CNFG_DBMANAGER, 6));
            config_map.insert(confinfo_pair(NS_CNFG_DBCONSTR, 7));
            config_map.insert(confinfo_pair(NS_CNFG_ANALOGBUFF, 8));
            config_map.insert(confinfo_pair(NS_CNFG_HISTORYPERIOD, 9));
            config_map.insert(confinfo_pair(NS_CNFG_LOGLEVEL, 10));
            config_map.insert(confinfo_pair(NS_CNFG_ADMINNAME, 11));
            config_map.insert(confinfo_pair(NS_CNFG_ADMINPASS, 12));
            config_map.insert(confinfo_pair(NS_CNFG_ADMINPORT, 13));
            config_map.insert(confinfo_pair(NS_CNFG_REMOTEPORT, 14));
            config_map.insert(confinfo_pair(NS_CNFG_OPCREMOTEPORT, 15));

            _state = disconnected;
        };

        bool adminintf::getexportbase(base_data& base, nodetype itemtype, const std::string& strcriteria, indx partid) {
            if (state() == connected) {

                if ((itemtype == NT_ROOT_SERVERS_AVAIL) || (NT_ROOT_SERVERS_AVAIL_R) ||
                        (itemtype == NT_ROOT_GROUPS) ||
                        (itemtype == NT_GROUP) || (itemtype == NT_UTIL_FINDER)) {
                    iteminfo_map groupmap_;
                    find_entities(NT_GROUP, groupmap_);
                    load_entities(NT_GROUP, groupmap_);
                    for (iteminfo_map::iterator it = groupmap_.begin(); it != groupmap_.end(); ++it) {
                        group_data tmp;
                        tmp.name = group(it->first).name();
                        ((groupstruct*) & tmp.groupinfo)->appid(group(it->first).appid());
                        ((groupstruct*) & tmp.groupinfo)->chanaltype(group(it->first).chanaltype());
                        ((groupstruct*) & tmp.groupinfo)->chanalnum(group(it->first).chanalnum());
                        //((groupstruct*) & tmp.groupinfo)->portnum(group(it->first).portnum());
                        ((groupstruct*) & tmp.groupinfo)->protocol(group(it->first).protocol());
                        tmp.changeset = MASK_GR_EXPORT1;
                        base.groups.push_back(tmp);
                    }
                }

                if ((itemtype == NT_ROOT_SERVERS_AVAIL) || (NT_ROOT_SERVERS_AVAIL_R) ||
                        (NT_ROOT_AGROUPS) ||
                        (itemtype == NT_AGROUP) || (itemtype == NT_UTIL_FINDER)) {
                    iteminfo_map agroupmap_;
                    find_entities(NT_AGROUP, agroupmap_);
                    load_entities(NT_AGROUP, agroupmap_);
                    for (iteminfo_map::iterator it = agroupmap_.begin(); it != agroupmap_.end(); ++it) {
                        agroup_data tmp;
                        tmp.name = agroup(it->first).name();
                        tmp.changeset = MASK_AGR_EXPORT1;
                        base.agroups.push_back(tmp);
                    }
                }

                if ((itemtype == NT_ROOT_SERVERS_AVAIL) || (NT_ROOT_SERVERS_AVAIL_R) ||
                        (itemtype == NT_ROOT_USERS) ||
                        (itemtype == NT_UTIL_FINDER)) {
                    iteminfo_map usermap_;
                    find_entities(NT_USER, usermap_);
                    load_entities(NT_USER, usermap_);
                    for (iteminfo_map::iterator it = usermap_.begin(); it != usermap_.end(); ++it) {
                        user_data tmp;
                        tmp.name = user(it->first).name();
                        tmp.password = user(it->first).password();
                        tmp.accesslevel = static_cast<num64> (user(it->first).accesslevel());
                        tmp.changeset = MASK_USER_EXPORT1;
                        base.users.push_back(tmp);
                    }
                }
                if ((itemtype == NT_ROOT_SERVERS_AVAIL) || (NT_ROOT_SERVERS_AVAIL_R) ||
                        (itemtype == NT_ROOT_GROUPS) ||
                        (itemtype == NT_GROUP) || (itemtype == NT_UTIL_FINDER)) {
                    iteminfo_map tagmap_;
                    find_entities(NT_TAG, tagmap_);
                    load_entities(NT_TAG, tagmap_);
                    for (iteminfo_map::iterator it = tagmap_.begin(); it != tagmap_.end(); ++it) {
                        tag_data tmp;
                        tmp.name = tag(it->first).name();
                        tmp.bind = tag(it->first).binding();
                        tmp.comment = tag(it->first).comment();
                        tmp.group = (groupsmap_.find(tag(it->first).group()) != groupsmap_.end()) ?
                                groupsmap_.find(tag(it->first).group())->second.name() : "";
                        tmp.onmsg = tag(it->first).onmsg();
                        tmp.offmsg = tag(it->first).offmsg();
                        tmp.almsg = tag(it->first).alarmmsg();
                        ((tagstruct*) & tmp.tginfo)->minraw(tag(it->first).minraw());
                        ((tagstruct*) & tmp.tginfo)->maxraw(tag(it->first).maxraw());
                        ((tagstruct*) & tmp.tginfo)->mineu(tag(it->first).mineu());
                        ((tagstruct*) & tmp.tginfo)->maxeu(tag(it->first).maxeu());
                        ((tagstruct*) & tmp.tginfo)->logdb(str_to<double>(tag(it->first).logdb()));
                        ((tagstruct*) & tmp.tginfo)->type(tag(it->first).type());
                        ((tagstruct*) & tmp.tginfo)->logged(tag(it->first).logged());
                        ((tagstruct*) & tmp.tginfo)->onmsged(tag(it->first).onmsged());
                        ((tagstruct*) & tmp.tginfo)->offmsged(tag(it->first).offmsged());
                        ((tagstruct*) & tmp.tginfo)->alarmcase(tag(it->first).alarmcase());
                        ((tagstruct*) & tmp.tginfo)->alarmconstr(tag(it->first).alarmconst());
                        ((tagstruct*) & tmp.tginfo)->devdb(str_to<double>(tag(it->first).devdb()));
                        ((tagstruct*) & tmp.tginfo)->alarmlevel(tag(it->first).alarmlevel());
                        tmp.changeset = MASK_RT_EXPORT1;
                        if ((itemtype != NT_GROUP) ||
                                ((itemtype == NT_GROUP) && (tag(it->first).group() == partid)))
                            base.tags.push_back(tmp);
                    }
                }
                return true;
            }
            return false;
        }

        bool adminintf::setimportbase(base_data& base, const std::string& strcriteria) {

            int_dvncierror_map tmp_errmap;
            str_indx_map grp_map;
            iteminfo_map grpit_map;
            str_indx_map newit_map;
            indx_set ent_set;
            iteminfo_map out_map;
            grp_map.clear();
            out_map.clear();
            clearerrors();
            num64 rewritetmp = base.options;

            ent_set.clear();
            newit_map.clear();
            if (base.groups.size() > 0) {
                for (vect_group_data::iterator it = base.groups.begin(); it != base.groups.end(); ++it) {
                    iteminfo_pair pair_;
                    insert_entity(NT_GROUP, 0, pair_, it->name);
                    if (pair_.first != npos) {
                        ent_set.insert(pair_.first);
                        newit_map.insert(str_indx_pair(it->name, pair_.first));
                        merge_entities(NT_GROUP, pair_.first);
                    } else {
                        if (errmap.size() > 0)
                            tmp_errmap.insert(int_dvncierror_pair(tmp_errmap.size(), errmap.begin()->second));
                    }
                }

                load_entities(NT_GROUP, ent_set);

                for (vect_group_data::iterator it = base.groups.begin(); it != base.groups.end(); ++it) {
                    iteminfo_pair pair_;
                    pair_.first = newit_map.find(it->name) != newit_map.end() ? newit_map.find(it->name)->second : npos;
                    if (pair_.first != npos) {

                        group(pair_.first).appid(((groupstruct*) & it->groupinfo)->appid());
                        group(pair_.first).chanaltype(((groupstruct*) & it->groupinfo)->chanaltype());
                        group(pair_.first).chanalnum(((groupstruct*) & it->groupinfo)->chanalnum());
                        group(pair_.first).chanaltype(((groupstruct*) & it->groupinfo)->chanaltype());
                        //group(pair_.first).portnum(((groupstruct*) & it->groupinfo)->portnum());
                        group(pair_.first).protocol(((groupstruct*) & it->groupinfo)->protocol());

                        group(pair_.first).timeout(((groupstruct*) & it->groupinfo)->timeout());
                        group(pair_.first).deadbound(((groupstruct*) & it->groupinfo)->deadbound());
                        group(pair_.first).grouprate(((groupstruct*) & it->groupinfo)->grouprate());
                        group(pair_.first).blocksize(((groupstruct*) & it->groupinfo)->blocksize());
                        group(pair_.first).archblocksize(((groupstruct*) & it->groupinfo)->archblocksize());
                        group(pair_.first).trycount(((groupstruct*) & it->groupinfo)->trycount());
                        group(pair_.first).utiloperation(((groupstruct*) & it->groupinfo)->utiloperation());
                        group(pair_.first).indicateto(((groupstruct*) & it->groupinfo)->indicateto());

                        merge_entities(NT_GROUP, pair_.first);
                    }
                }

                if (ent_set.size() > 0) merge_entities(NT_GROUP, ent_set, out_map);
            }



            ent_set.clear();
            find_entities(NT_GROUP, grpit_map);
            for (iteminfo_map::iterator it = grpit_map.begin(); it != grpit_map.end(); ++it) {
                grp_map.insert(str_indx_pair(it->second.name(), it->first));
            }



            ent_set.clear();
            newit_map.clear();
            if (base.tags.size() > 0) {
                indx indxgr = npos;
                for (vect_tag_data::iterator it = base.tags.begin(); it != base.tags.end(); ++it) {
                    indxgr = grp_map.find(it->group)->second;
                    if (indxgr != npos) {
                        newit_map.insert(str_indx_pair(it->name, indxgr));
                    }
                }
                insert_entities(NT_TAG, indxgr, newit_map);
                for (str_indx_map::iterator it = newit_map.begin(); it != newit_map.end(); ++it) {
                    if (it->second != npos) ent_set.insert(it->second);
                    else tmp_errmap.insert(int_dvncierror_pair(tmp_errmap.size(), dvncierror(ERROR_PARENTENTETY_CORRECT, it->first)));
                }

                load_entities(NT_TAG, ent_set);

                for (vect_tag_data::iterator it = base.tags.begin(); it != base.tags.end(); ++it) {
                    iteminfo_pair pair_;
                    pair_.first = newit_map.find(it->name) != newit_map.end() ? newit_map.find(it->name)->second : npos;
                    if (pair_.first != npos) {

                        tag(pair_.first).comment(it->comment);

                        tag(pair_.first).binding(it->bind);
                        tag(pair_.first).eu(it->ue);
                        tag(pair_.first).onmsg(it->onmsg);
                        tag(pair_.first).offmsg(it->offmsg);
                        tag(pair_.first).alarmmsg(it->almsg);
                        tag(pair_.first).type(((tagstruct*) & it->tginfo)->type());
                        tag(pair_.first).logged(((tagstruct*) & it->tginfo)->logged());
                        tag(pair_.first).logdb(to_str<double>(((tagstruct*) & it->tginfo)->logdb()));
                        tag(pair_.first).mineu(((tagstruct*) & it->tginfo)->mineu_str());
                        tag(pair_.first).maxeu(((tagstruct*) & it->tginfo)->maxeu_str());
                        tag(pair_.first).minraw(((tagstruct*) & it->tginfo)->minraw_str());
                        tag(pair_.first).maxraw(((tagstruct*) & it->tginfo)->maxraw_str());
                        tag(pair_.first).offmsged(((tagstruct*) & it->tginfo)->onmsged());
                        tag(pair_.first).onmsged(((tagstruct*) & it->tginfo)->offmsged());
                        tag(pair_.first).alarmlevel(((tagstruct*) & it->tginfo)->alarmlevel());
                        tag(pair_.first).devdb("0");
                        tag(pair_.first).alarmcase(((tagstruct*) & it->tginfo)->alarmcase());
                        tag(pair_.first).alarmconst(((tagstruct*) & it->tginfo)->alarmconst_str());
                        merge_entities(NT_TAG, pair_.first);
                    }
                }

                if (ent_set.size() > 0) merge_entities(NT_TAG, ent_set, out_map);
            }


            ent_set.clear();
            newit_map.clear();
            if (base.agroups.size() > 0) {
                for (vect_agroup_data::iterator it = base.agroups.begin(); it != base.agroups.end(); ++it) {
                    iteminfo_pair pair_;
                    insert_entity(NT_AGROUP, 0, pair_, it->name);
                    if (pair_.first != npos) {
                        ent_set.insert(pair_.first);
                    } else {
                        if (errmap.size() > 0)
                            tmp_errmap.insert(int_dvncierror_pair(tmp_errmap.size(), errmap.begin()->second));
                    }
                }

                if (ent_set.size() > 0) merge_entities(NT_AGROUP, ent_set, out_map);
            }




            ent_set.clear();
            newit_map.clear();
            if (base.users.size() > 0) {
                for (vect_user_data::iterator it = base.users.begin(); it != base.users.end(); ++it) {
                    iteminfo_pair pair_;
                    insert_entity(NT_USER, 0, pair_, it->name);
                    if (pair_.first != npos) {
                        ent_set.insert(pair_.first);
                        newit_map.insert(str_indx_pair(it->name, pair_.first));
                        merge_entities(NT_USER, pair_.first);
                    } else {
                        if (errmap.size() > 0)
                            tmp_errmap.insert(int_dvncierror_pair(tmp_errmap.size(), errmap.begin()->second));
                    }
                }

                load_entities(NT_USER, ent_set);

                for (vect_user_data::iterator it = base.users.begin(); it != base.users.end(); ++it) {
                    iteminfo_pair pair_;
                    pair_.first = newit_map.find(it->name) != newit_map.end() ? newit_map.find(it->name)->second : npos;
                    if (pair_.first != npos) {
                        user(pair_.first).password(it->password);
                        user(pair_.first).accesslevel(static_cast<acclevtype> (it->accesslevel));
                        merge_entities(NT_USER, pair_.first);
                    }
                }
            }

            errmap.clear();
            errmap.insert(tmp_errmap.begin(), tmp_errmap.end());
            return true;
        }

        void adminintf::assign_vect_error_entity(vect_error_entity& val) const {
            val.clear();
            for (int_dvncierror_map::const_iterator it = errmap.begin(); it != errmap.end(); ++it) {
                error_entity tmperror;
                tmperror.code = it->second.code();
                tmperror.key = it->second.key();
                tmperror.str = it->second.str();
                val.push_back(tmperror);
            }
        }

        void adminintf::set_vect_error_entity(const vect_error_entity& val) {
            for (vect_error_entity::const_iterator it = val.begin(); it != val.end(); ++it) {
                dvncierror tmperr(static_cast<ns_error> (it->code), it->str, static_cast<indx> (it->key));
                adderror(tmperr);
            }
        }

        void adminintf::assign_sig(const iteminfo_map& mappack, vect_entitysig_data& val) const {

            val.clear();
            for (iteminfo_map::const_iterator it = mappack.begin(); it != mappack.end(); ++it) {
                entitysig_data tmpsinf;
                tmpsinf.key = static_cast<num64> (it->first);
                tmpsinf.name = it->second.name();
                tmpsinf.tpitem = it->second.typeex();
                val.push_back(tmpsinf);
            }
        }

        void adminintf::assign_tag_data(const indx_set& idset, vect_tag_data& val) const {

            val.clear();
            for (indx_set::const_iterator it = idset.begin(); it != idset.end(); ++it) {
                tag_data tmpentity;
                tmpentity.key = static_cast<num64> (*it);
                tmpentity.name = tag(*it).name();
                tmpentity.comment = tag(*it).comment();
                tmpentity.bind = tag(*it).binding();
                tmpentity.ue = tag(*it).eu();
                tmpentity.onmsg = tag(*it).onmsg();
                tmpentity.offmsg = tag(*it).offmsg();
                tmpentity.almsg = tag(*it).alarmmsg();
                tmpentity.changeset = 0;
                if (tag(*it)._struct())
                    memcpy((void*) &tmpentity.tginfo, tag(*it)._struct(), sizeof (tagstruct));
                val.push_back(tmpentity);
            }
        }

        void adminintf::assign_tag_data(const num64_vect& keys, vect_tag_data& val) const {
            indx_set tmp;
            keys >> tmp;
            assign_tag_data(tmp, val);
        }

        void adminintf::set_tag_data(const vect_tag_data& val, indx_set& idset) {
            idset.clear();
            for (vect_tag_data::const_iterator it = val.begin(); it != val.end(); ++it) {
                try {
                    num64 changeset = it->changeset;
                    indx id = static_cast<indx> (it->key);
                    idset.insert(id);
                    if ((changeset & MASK_RT_CHANGE_VALUE) != 0) {
                        tag(id).value(((ptagstruct) & it->tginfo)->value_str());
                    };
                    if ((changeset & MASK_RT_CHANGE_MINEU) != 0) {
                        tag(id).mineu(((ptagstruct) & it->tginfo)->mineu_str());
                    };
                    if ((changeset & MASK_RT_CHANGE_MAXEU) != 0) {
                        tag(id).maxeu(((ptagstruct) & it->tginfo)->maxeu_str());
                    };
                    if ((changeset & MASK_RT_CHANGE_MINRAW) != 0) {
                        tag(id).minraw(((ptagstruct) & it->tginfo)->minraw_str());
                    };
                    if ((changeset & MASK_RT_CHANGE_MAXRAW) != 0) {
                        tag(id).maxraw(((ptagstruct) & it->tginfo)->maxraw_str());
                    };
                    if ((changeset & MASK_RT_CHANGE_MINRAW) != 0) {
                        tag(id).logdb(to_str<double>(((ptagstruct) & it->tginfo)->logdb()));
                    };
                    if ((changeset & MASK_RT_CHANGE_ALARMCONST) != 0) {
                        tag(id).alarmconst(((ptagstruct) & it->tginfo)->alarmconst_str());
                    };
                    if ((changeset & MASK_RT_CHANGE_MAXRAW) != 0) {
                        tag(id).devdb(to_str(((ptagstruct) & it->tginfo)->devdb()));
                    };
                    if ((changeset & MASK_RT_CHANGE_NAME) != 0) {
                        tag(id).name(it->name);
                    };
                    if ((changeset & MASK_RT_CHANGE_COMMENT) != 0) {
                        tag(id).comment(it->comment);
                    };
                    if ((changeset & MASK_RT_CHANGE_BINDING) != 0) {
                        tag(id).binding(it->bind);
                    };
                    if ((changeset & MASK_RT_CHANGE_EU) != 0) {
                        tag(id).eu(it->ue);
                    };
                    if ((changeset & MASK_RT_CHANGE_ONMSGTXT) != 0) {
                        tag(id).onmsg(it->onmsg);
                    };
                    if ((changeset & MASK_RT_CHANGE_OFFMSGTXT) != 0) {
                        tag(id).offmsg(it->offmsg);
                    };
                    if ((changeset & MASK_RT_CHANGE_ALMSGTXT) != 0) {
                        tag(id).alarmmsg(it->almsg);
                    };
                    if ((changeset & MASK_RT_CHANGE_LOGGED) != 0) {
                        tag(id).logged(((ptagstruct) & it->tginfo)->logged());
                    };
                    if ((changeset & MASK_RT_CHANGE_ONMSG) != 0) {
                        tag(id).onmsged(((ptagstruct) & it->tginfo)->onmsged());
                    };
                    if ((changeset & MASK_RT_CHANGE_OFFMSG) != 0) {
                        tag(id).offmsged(((ptagstruct) & it->tginfo)->offmsged());
                    };
                    if ((changeset & MASK_RT_CHANGE_TYPE) != 0) {
                        tag(id).type(((ptagstruct) & it->tginfo)->type());
                    };
                    if ((changeset & MASK_RT_CHANGE_ALLEVEL) != 0) {
                        tag(id).alarmlevel(((ptagstruct) & it->tginfo)->alarmlevel());
                    };
                    if ((changeset & MASK_RT_CHANGE_ALWACTIVE) != 0) {
                        tag(id).alwactive(((ptagstruct) & it->tginfo)->alwactive());
                    };
                    if ((changeset & MASK_RT_CHANGE_RANG) != 0) {
                        tag(id).rangable(((ptagstruct) & it->tginfo)->rangable());
                    };
                    if ((changeset & MASK_RT_CHANGE_ALCASE) != 0) {
                        tag(id).alarmcase(((ptagstruct) & it->tginfo)->alarmcase());
                    };
                    if ((changeset & MASK_RT_CHANGE_RW) != 0) {
                        tag(id).rwtype(((ptagstruct) & it->tginfo)->rwtype());
                    };
                    if ((changeset & MASK_RT_CHANGE_GROUP) != 0) {
                        tag(id).group(((ptagstruct) & it->tginfo)->group());
                    };
                    if ((changeset & MASK_RT_CHANGE_AGROUP) != 0) {
                        tag(id).agroup(((ptagstruct) & it->tginfo)->agroup());
                    };
                    if ((changeset & MASK_RT_CHANGE_REPPER) != 0) {
                        tag(id).reporthistory(((ptagstruct) & it->tginfo)->reporthistory());
                    };
                    if ((changeset & MASK_RT_CHANGE_DELT) != 0) {
                        tag(id).reportsubdelt(((ptagstruct) & it->tginfo)->reportsubdelt());
                    };
                    if ((changeset & MASK_RT_CHANGE_STAT) != 0) {
                        tag(id).reportstatistic(((ptagstruct) & it->tginfo)->reportstatistic());
                    };
                    if ((changeset & MASK_RT_CHANGE_ACCESSL) != 0) {
                        tag(id).reporthistory(((ptagstruct) & it->tginfo)->accesslevel());
                    }
                    if (changeset != 0) merge_entities(NT_TAG, id);
                }                catch (dvncierror& err_) {
                    adderror(err_);
                }
            }
        }

        void adminintf::assign_group_data(const indx_set& idset, vect_group_data& val) const {
            val.clear();
            for (indx_set::const_iterator it = idset.begin(); it != idset.end(); ++it) {
                group_data tmpentity;
                tmpentity.key = static_cast<num64> (*it);
                tmpentity.name = group(*it).name();
                tmpentity.host = group(*it).host();
                tmpentity.user = group(*it).user();
                tmpentity.password = group(*it).password();
                tmpentity.server = group(*it).server();
                tmpentity.group = group(*it).group();
                tmpentity.port = group(*it).port();
                tmpentity.topic = group(*it).topic();
                tmpentity.ether = group(*it).ether();
                tmpentity.changeset = 0;
                if (group(*it)._struct())
                    memcpy((void*) &tmpentity.groupinfo, group(*it)._struct(), sizeof (groupstruct));
                val.push_back(tmpentity);
            }
        }

        void adminintf::assign_group_data(const num64_vect& keys, vect_group_data& val) const {
            indx_set tmp;
            keys >> tmp;
            assign_group_data(tmp, val);
        }

        void adminintf::set_group_data(const vect_group_data& val, indx_set& idset) {
            idset.clear();
            for (vect_group_data::const_iterator it = val.begin(); it != val.end(); ++it) {
                num64 changeset = it->changeset;
                indx id = static_cast<indx> (it->key);
                idset.insert(id);
                if ((changeset & MASK_GR_CHANGE_NAME) != 0) {
                    group(id).name(it->name);
                };
                if ((changeset & MASK_GR_CHANGE_HOST) != 0) {
                    group(id).host(it->host);
                };
                if ((changeset & MASK_GR_CHANGE_USER) != 0) {
                    group(id).user(it->user);
                };
                if ((changeset & MASK_GR_CHANGE_PASS) != 0) {
                    group(id).password(it->password);
                };
                if ((changeset & MASK_GR_CHANGE_SERVER) != 0) {
                    group(id).server(it->server);
                };
                if ((changeset & MASK_GR_CHANGE_GROUP) != 0) {
                    group(id).group(it->group);
                };
                if ((changeset & MASK_GR_CHANGE_PORT) != 0) {
                    group(id).port(it->port);
                };
                if ((changeset & MASK_GR_CHANGE_TOPIC) != 0) {
                    group(id).server(it->topic);
                };
                if ((changeset & MASK_GR_CHANGE_ETHER) != 0) {
                    group(id).ether(it->ether);
                };
                if ((changeset & MASK_GR_CHANGE_APPID) != 0) {
                    group(id).appid(pgroupstruct(&it->groupinfo)->appid());
                };
                if ((changeset & MASK_GR_CHANGE_CHTYPE) != 0) {
                    group(id).chanaltype(pgroupstruct(&it->groupinfo)->chanaltype());
                };
                if ((changeset & MASK_GR_CHANGE_CHNUM) != 0) {
                    group(id).chanalnum(pgroupstruct(&it->groupinfo)->chanalnum());
                };
                if ((changeset & MASK_GR_CHANGE_CHDEVNUM) != 0) {
                    group(id).devnum(pgroupstruct(&it->groupinfo)->devnum());
                };
                if ((changeset & MASK_GR_CHANGE_DEVNUM) != 0) {
                    group(id).protocol(pgroupstruct(&it->groupinfo)->protocol());
                };
                if ((changeset & MASK_GR_CHANGE_CONFIG) != 0) {
                    group(id).config(const_cast<void*> (pgroupstruct(&it->groupinfo)->config()));
                };
                if ((changeset & MASK_GR_CHANGE_TO) != 0) {
                    group(id).timeout(pgroupstruct(&it->groupinfo)->timeout());
                };
                if ((changeset & MASK_GR_CHANGE_DB) != 0) {
                    group(id).deadbound(pgroupstruct(&it->groupinfo)->deadbound());
                };
                if ((changeset & MASK_GR_CHANGE_GR) != 0) {
                    group(id).grouprate(pgroupstruct(&it->groupinfo)->grouprate());
                };
                if ((changeset & MASK_GR_CHANGE_BS) != 0) {
                    group(id).blocksize(pgroupstruct(&it->groupinfo)->blocksize());
                };
                if ((changeset & MASK_GR_CHANGE_ABS) != 0) {
                    group(id).archblocksize(pgroupstruct(&it->groupinfo)->archblocksize());
                };
                if ((changeset & MASK_GR_CHANGE_TCNT) != 0) {
                    group(id).trycount(pgroupstruct(&it->groupinfo)->trycount());
                };
                if ((changeset & MASK_GR_CHANGE_TCNT) != 0) {
                    group(id).utiloperation(pgroupstruct(&it->groupinfo)->utiloperation());
                };
                if ((changeset & MASK_GR_CHANGE_INDTO) != 0) {
                    group(id).indicateto(pgroupstruct(&it->groupinfo)->indicateto());
                };
                if (changeset != 0) merge_entities(NT_GROUP, id);
            }
        }

        void adminintf::assign_agroup_data(const indx_set& idset, vect_agroup_data& val) const {

            val.clear();
            for (indx_set::const_iterator it = idset.begin(); it != idset.end(); ++it) {
                agroup_data tmpentity;
                tmpentity.key = static_cast<num64> (*it);
                tmpentity.name = agroup(*it).name();
                tmpentity.headername = agroup(*it).headername();
                tmpentity.changeset = 0;
                if (agroup(*it)._struct())
                    memcpy((void*) &tmpentity.agroupinfo, agroup(*it)._struct(), sizeof (agroupstruct));
                val.push_back(tmpentity);
            }
        }

        void adminintf::assign_agroup_data(const num64_vect& keys, vect_agroup_data& val) const {
            indx_set tmp;
            keys >> tmp;
            assign_agroup_data(tmp, val);
        }

        void adminintf::set_agroup_data(const vect_agroup_data& val, indx_set& idset) {
            idset.clear();
            for (vect_agroup_data::const_iterator it = val.begin(); it != val.end(); ++it) {
                num64 changeset = it->changeset;
                indx id = static_cast<indx> (it->key);
                idset.insert(id);
                if ((changeset & MASK_AGR_CHANGE_NAME) != 0) {
                    agroup(id).name(it->name);
                };
                if ((changeset & MASK_AGR_CHANGE_HEADNAME) != 0) {
                    agroup(id).headername(it->headername);
                };
                if (changeset != 0) merge_entities(NT_GROUP, id);
            }
        }

        void adminintf::assign_user_data(const indx_set& idset, vect_user_data& val) const {
            val.clear();
            for (indx_set::const_iterator it = idset.begin(); it != idset.end(); ++it) {
                user_data tmpentity;
                tmpentity.key = static_cast<num64> (*it);
                tmpentity.changeset = 0;
                tmpentity.name = user(*it).name();
                tmpentity.password = user(*it).password();
                tmpentity.filter = user(*it).filter();
                tmpentity.role = static_cast<num64> (user(*it).role());
                tmpentity.accesslevel = static_cast<num64> (user(*it).accesslevel());
                val.push_back(tmpentity);
            }
        }

        void adminintf::assign_user_data(const num64_vect& keys, vect_user_data& val) const {
            indx_set tmp;
            keys >> tmp;
            assign_user_data(tmp, val);
        }

        void adminintf::set_user_data(const vect_user_data& val, indx_set& idset) {
            idset.clear();
            for (vect_user_data::const_iterator it = val.begin(); it != val.end(); ++it) {
                num64 changeset = it->changeset;
                indx id = static_cast<indx> (it->key);
                idset.insert(id);
                if ((changeset & MASK_USER_CHANGE_NAME) != 0) {
                    user(id).name(it->name);
                };
                if ((changeset & MASK_USER_CHANGE_PASSWORD) != 0) {
                    user(id).password(it->password);
                };
                if ((changeset & MASK_USER_CHANGE_FILTER) != 0) {
                    user(id).filter(it->filter);
                };
                if ((changeset & MASK_USER_CHANGE_ROLE) != 0) {
                    user(id).role(static_cast<accessruletype> (it->role));
                };
                if ((changeset & MASK_USER_CHANGE_LEVEL) != 0) {
                    user(id).accesslevel(static_cast<acclevtype> (it->accesslevel));
                };
                if (changeset != 0) merge_entities(NT_USER, id);
            }
        }

        void adminintf::assign_accessrule_data(const indx_set& idset, vect_accessrule_data& val) const {
            val.clear();
            for (indx_set::const_iterator it = idset.begin(); it != idset.end(); ++it) {
                accessrule_data tmpentity;
                tmpentity.key = static_cast<num64> (*it);
                tmpentity.changeset = 0;
                tmpentity.name = accessrule(*it).name();
                tmpentity.user = accessrule(*it).user();
                tmpentity.filter = accessrule(*it).filter();
                tmpentity.appid = static_cast<num64> (accessrule(*it).appid());
                tmpentity.accessrule = static_cast<num64> (accessrule(*it).accessrule());
                tmpentity.accesslevel = static_cast<num64> (accessrule(*it).accesslevel());
                tmpentity.role = static_cast<num64> (accessrule(*it).role());
                val.push_back(tmpentity);
            }
        }

        void adminintf::assign_accessrule_data(const num64_vect& keys, vect_accessrule_data& val) const {
            indx_set tmp;
            keys >> tmp;
            assign_accessrule_data(tmp, val);
        }

        void adminintf::set_accessrule_data(const vect_accessrule_data& val, indx_set& idset) {
            idset.clear();
            for (vect_accessrule_data::const_iterator it = val.begin(); it != val.end(); ++it) {
                num64 changeset = it->changeset;
                indx id = static_cast<indx> (it->key);
                idset.insert(id);
                if ((changeset & MASK_AR_CHANGE_NAME) != 0) {
                    accessrule(id).name(it->name);
                };
                if ((changeset & MASK_AR_CHANGE_USER) != 0) {
                    accessrule(id).user(it->user);
                };
                if ((changeset & MASK_AR_CHANGE_HOST) != 0) {
                    accessrule(id).host(it->host);
                };
                if ((changeset & MASK_AR_CHANGE_FILTER) != 0) {
                    accessrule(id).filter(it->filter);
                };
                if ((changeset & MASK_AR_CHANGE_APPID) != 0) {
                    accessrule(id).appid(static_cast<appidtype> (it->appid));
                };
                if ((changeset & MASK_AR_CHANGE_RULE) != 0) {
                    accessrule(id).accessrule(static_cast<accessruletype> (it->accessrule));
                };
                if ((changeset & MASK_AR_CHANGE_ROLE) != 0) {
                    accessrule(id).role(static_cast<accessruletype> (it->role));
                };
                if ((changeset & MASK_AR_CHANGE_AL) != 0) {
                    accessrule(id).accesslevel(static_cast<acclevtype> (it->accesslevel));
                };
                if (changeset != 0) merge_entities(NT_ACCESSRULE, id);
            }
        }

        void adminintf::assign_service_data(const indx_set& idset, vect_service_data& val) const {
            val.clear();
            for (indx_set::const_iterator it = idset.begin(); it != idset.end(); ++it) {
                service_data tmpentity;
                tmpentity.key = static_cast<num64> (*it);
                tmpentity.changeset = 0;
                tmpentity.name = service(*it).displayname();
                tmpentity.path = service(*it).path();
                tmpentity.starttype = service(*it).starttype();
                tmpentity.status = service(*it).status();
                val.push_back(tmpentity);
            }
        }

        void adminintf::assign_service_data(const num64_vect& keys, vect_service_data& val) const {
            indx_set tmp;
            keys >> tmp;
            assign_service_data(tmp, val);
        }

        void adminintf::set_service_data(const vect_service_data& val, indx_set& idset) {
            idset.clear();
            for (vect_service_data::const_iterator it = val.begin(); it != val.end(); ++it) {
                num64 changeset = it->changeset;
                indx id = static_cast<indx> (it->key);
                idset.insert(id);
                if ((changeset & MASK_GR_CHANGE_STARTTP) != 0) {
                    service(id).starttype(it->starttype);
                };
                if (changeset != 0) merge_entities(NT_SERVICE, id);
            }
        }

        void adminintf::assign_meta_data(const indx_set& idset, nodetype metatp, vect_meta_data& val) const {
            val.clear();
            for (indx_set::const_iterator it = idset.begin(); it != idset.end(); ++it) {
                meta_data tmpentity;
                tmpentity.key = static_cast<num64> (*it);
                tmpentity.changeset = 0;
                tmpentity.meta_type = static_cast<num64> (metatp);
                propertymeta_ids_map* tmp_regesty = meta().propertymap(metatp);
                if (tmp_regesty) {
                    for (propertymeta_ids_map::iterator iti = tmp_regesty->begin(); iti != tmp_regesty->end(); ++iti) {
                        if ((iti->second >= 0) && (iti->second < 20)) {
                            tmpentity.str_data[iti->second] = meta(metatp, *it).property(iti->first);
                        }
                    }
                };
                val.push_back(tmpentity);
            }
        }

        void adminintf::assign_meta_data(const num64_vect& keys, nodetype metatp, vect_meta_data& val) const {
            indx_set tmp;
            keys >> tmp;
            assign_meta_data(tmp, metatp, val);
        }

        void adminintf::set_meta_data(const vect_meta_data& val, indx_set& idset) {
            idset.clear();
            for (vect_meta_data::const_iterator it = val.begin(); it != val.end(); ++it) {
                num64 changeset = it->changeset;
                indx id = static_cast<indx> (it->key);
                idset.insert(id);
                propertymeta_ids_map* tmp_regesty = meta().propertymap(static_cast<nodetype> (it->meta_type));
                if (tmp_regesty) {
                    for (propertymeta_ids_map::const_iterator iti = tmp_regesty->begin(); iti != tmp_regesty->end(); ++iti) {
                        if (((changeset & (0x1LL << iti->second))) && (iti->second >= 0) && (iti->second < 20)) {
                            meta(static_cast<nodetype> (it->meta_type), id).property(iti->first, it->str_data[iti->second]);
                        }
                    }
                }
                if (changeset != 0) merge_entities(static_cast<nodetype> (it->meta_type), id);
            }
        }

        void adminintf::assign_config_data(const indx_set& idset, config_data& val) const {
            for (confinfo_map::const_iterator it = config_map.begin(); it != config_map.end(); ++it) {
                if (it->second < 20) val.str_data[it->second] = conf_property(it->first);
            }
        }

        ns_error adminintf::load_entities(nodetype ittp, iteminfo_map& mappack) {
            indx_set idset;
            idset.clear();
            for (iteminfo_map::iterator it = mappack.begin(); it != mappack.end(); ++it)
                idset.insert(it->first);
            return load_entities(ittp, idset);
        }

        ns_error adminintf::load_entity(nodetype ittp, indx id) {
            indx_set idset;
            idset.clear();
            idset.insert(id);
            return load_entities(ittp, idset);
        }

        void adminintf::assign_config_data(const num64_vect& keys, config_data& val) const {
            indx_set tmp;
            keys >> tmp;
            assign_config_data(tmp, val);
        }

        void adminintf::set_config_data(const config_data& val, indx_set& idset) {
            DEBUG_STR_DVNCI(set_config_data)
            DEBUG_STR_VAL_DVNCI(set_config_data, val.changeset)
            for (confinfo_map::const_iterator it = config_map.begin(); it != config_map.end(); ++it) {
                DEBUG_STR_VAL_DVNCI(set_config_data, it->first)
                DEBUG_STR_VAL_DVNCI(set_config_data, it->second)
                if ((it->second < 20) && (((val.changeset) &(0x1LL << it->second)) != 0))
                    conf_property(it->first, val.str_data[it->second]);
            }
        }

        num16 adminintf::generate_impl(req_entitysigs& req, resp_entitysigs& resp) {

            iteminfo_map mappack;
            select_entities(static_cast<nodetype> (req.tpitem), mappack, static_cast<indx> (req.parentid), req.strcriteria, 0);
            resp.err = 0;
            resp.tpreq = req.tpitem;
            assign_sig(mappack, resp.sigs);
            return RPC_OPERATION_RESP_ENTITYSIGS;
        }

        num16 adminintf::generate_impl(req_tags& req, resp_tags& resp) {

            resp.err = 0;
            assign_tag_data(req.keys, resp.tags);
            return RPC_OPERATION_RESP_TAGS;
        }

        num16 adminintf::generate_impl(req_sendtags& req, resp_sendtags& resp) {
            indx_set idset;
            clearerrors();
            set_tag_data(req.tags, idset);
            assign_tag_data(idset, resp.tags);
            assign_vect_error_entity(resp.error);
            return RPC_OPERATION_RESP_SENDTAGS;
        }

        num16 adminintf::generate_impl(req_groups& req, resp_groups& resp) {
            resp.err = 0;
            assign_group_data(req.keys, resp.groups);
            return RPC_OPERATION_RESP_GROUPS;
        }

        num16 adminintf::generate_impl(req_sendgroups& req, resp_sendgroups& resp) {
            indx_set idset;
            clearerrors();
            set_group_data(req.groups, idset);
            assign_group_data(idset, resp.groups);
            assign_vect_error_entity(resp.error);
            return RPC_OPERATION_RESP_SENDGROUPS;
        }

        num16 adminintf::generate_impl(req_agroups& req, resp_agroups& resp) {
            resp.err = 0;
            assign_agroup_data(req.keys, resp.agroups);
            return RPC_OPERATION_RESP_AGROUPS;
        }

        num16 adminintf::generate_impl(req_sendagroups& req, resp_sendagroups& resp) {
            indx_set idset;
            clearerrors();
            set_agroup_data(req.agroups, idset);
            assign_agroup_data(idset, resp.agroups);
            assign_vect_error_entity(resp.error);
            return RPC_OPERATION_RESP_SENDAGROUPS;
        }

        num16 adminintf::generate_impl(req_users& req, resp_users& resp) {
            resp.err = 0;
            assign_user_data(req.keys, resp.users);
            return RPC_OPERATION_RESP_USERS;
        }

        num16 adminintf::generate_impl(req_sendusers& req, resp_sendusers& resp) {
            indx_set idset;
            clearerrors();
            set_user_data(req.users, idset);
            assign_user_data(idset, resp.users);
            assign_vect_error_entity(resp.error);
            return RPC_OPERATION_RESP_SENDUSERS;
        }

        num16 adminintf::generate_impl(req_accessrules& req, resp_accessrules& resp) {
            resp.err = 0;
            assign_accessrule_data(req.keys, resp.accessrules);
            return RPC_OPERATION_RESP_ACCESSRULES;
        }

        num16 adminintf::generate_impl(req_sendaccessrules& req, resp_sendaccessrules& resp) {
            indx_set idset;
            clearerrors();
            set_accessrule_data(req.accessrules, idset);
            assign_accessrule_data(idset, resp.accessrules);
            assign_vect_error_entity(resp.error);
            return RPC_OPERATION_RESP_SENDACCESSRULES;
        }

        num16 adminintf::generate_impl(req_services& req, resp_services& resp) {
            resp.err = 0;
            assign_service_data(req.keys, resp.services);
            return RPC_OPERATION_RESP_SERVICES;
        }

        num16 adminintf::generate_impl(req_sendservices& req, resp_sendservices& resp) {
            indx_set idset;
            clearerrors();
            set_service_data(req.services, idset);
            assign_service_data(idset, resp.services);
            assign_vect_error_entity(resp.error);
            return RPC_OPERATION_RESP_SENDSERVICES;
        }

        num16 adminintf::generate_impl(req_metas& req, resp_metas& resp) {
            resp.err = 0;
            assign_meta_data(req.keys, static_cast<nodetype> (req.meta_type), resp.metas);
            return RPC_OPERATION_RESP_METAS;
        }

        num16 adminintf::generate_impl(req_sendmetas& req, resp_sendmetas& resp) {
            indx_set idset;
            clearerrors();
            set_meta_data(req.metas, idset);
            if (req.metas.begin() != req.metas.end()) {
                assign_meta_data(idset, static_cast<nodetype> (req.metas.begin()->meta_type), resp.metas);
            }
            assign_vect_error_entity(resp.error);
            return RPC_OPERATION_RESP_SENDMETAS;
        }

        num16 adminintf::generate_impl(req_addentity& req, resp_addentity& resp) {
            clearerrors();
            iteminfo_pair newentety;
            insert_entity(static_cast<nodetype> (req.tpitem), static_cast<indx> (req.parentkey), newentety, req.newname);
            assign_vect_error_entity(resp.error);
            resp.sig.key = newentety.first;
            resp.sig.name = newentety.second.name();
            resp.sig.tpitem = newentety.second.typeex();
            return RPC_OPERATION_RESP_ADDENTITY;
        }

        num16 adminintf::generate_impl(req_dupentity& req, resp_dupentity& resp) {
            clearerrors();
            iteminfo_pair newentety;
            duplicate_entity(static_cast<nodetype> (req.tpitem), static_cast<indx> (req.soursekey), req.newname, newentety);
            assign_vect_error_entity(resp.error);
            resp.sig.key = newentety.first;
            resp.sig.name = newentety.second.name();
            resp.sig.tpitem = newentety.second.typeex();
            return RPC_OPERATION_RESP_DUPENTITY;
        }

        num16 adminintf::generate_impl(req_removeentity& req, resp_removeentity& resp) {
            indx_set tmpset;
            req.keys >> tmpset;
            delete_entities(static_cast<nodetype> (req.tpitem), tmpset);
            assign_vect_error_entity(resp.error);
            return RPC_OPERATION_RESP_REMOVEENTITY;
        }

        num16 adminintf::generate_impl(req_alarms& req, resp_alarms& resp) {
            alarms_mf();
            resp.vers = alarm().version();
            if (req.vers != resp.vers) {
                alarm().assign_data(resp.lines);
            }
            return RPC_OPERATION_RESP_ALARMS;
        }

        num16 adminintf::generate_impl(req_registry& req, resp_registry& resp) {
            regs_mf();
            resp.vers = registry().version();
            if (req.vers != resp.vers) {
                registry().assign_data(resp.lines);
            }
            return RPC_OPERATION_RESP_REGISTRY;
        }

        num16 adminintf::generate_impl(req_commands& req, resp_commands& resp) {
            commands_mf();
            resp.vers = command().version();
            if (req.vers != resp.vers) {
                command().assign_data(resp.lines);
            }
            return RPC_OPERATION_RESP_COMMANDS;
        }

        num16 adminintf::generate_impl(req_clients& req, resp_clients& resp) {
            clients_mf();
            resp.vers = client().version();
            if (req.vers != resp.vers) {
                client().assign_data(resp.lines);
            }
            return RPC_OPERATION_RESP_CLIENTS;
        }

        num16 adminintf::generate_impl(req_journal& req, resp_journal& resp) {
            journal().assign_data(resp.lines);
            resp.guid = journal().guid();
            resp.cursor = journal().cursor();
            resp.cnt = journal().count();

            return RPC_OPERATION_RESP_JOURNAL;
        }

        num16 adminintf::generate_impl(req_debug& req, resp_debug& resp) {
            debug().assign_data(resp.lines);
            resp.guid = debug().guid();
            resp.cursor = debug().cursor();
            resp.cnt = debug().count();
            return RPC_OPERATION_RESP_DEBUG;
        }

        num16 adminintf::generate_impl(req_config& req, resp_config& resp) {
            try {
                resp.config.changeset = 0;
                indx_set idset;
                assign_config_data(idset, resp.config);
            }            catch (...) {
            }
            return RPC_OPERATION_RESP_CONFIG;
        }

        num16 adminintf::generate_impl(req_sendconfig& req, resp_sendconfig& resp) {
            try {
                clearerrors();
                indx_set idset;
                set_config_data(req.config, idset);
                assign_config_data(idset, resp.config);
                assign_vect_error_entity(resp.error);
            }            catch (...) {
            }
            return RPC_OPERATION_RESP_SENDCONFIG;
        }

        num16 adminintf::generate_impl(req_adminoperation& req, resp_adminoperation& resp) {
            try {
                clearerrors();
                num64 oper = req.numpar1;
                resp.err = 0;
                switch (oper) {
                    case OPERATION_INCCOUNTALL:
                    {
                        operation_setallcounter();
                        break;
                    }
                    case OPERATION_DECCOUNTALL:
                    {
                        operation_setallcounter(false);
                        break;
                    }
                    case OPERATION_SETALL_VALID:
                    {
                        operation_setallvalid(static_cast<vlvtype> (req.numpar2));
                        break;
                    }
                    case OPERATION_SETALL_INVALID:
                    {
                        operation_setallvalid(static_cast<vlvtype> (req.numpar2));
                        break;
                    }
                    case OPERATION_ACTION_KVIT:
                    {
                        operation_kvit();
                        break;
                    }
                    case OPERATION_KVIT_GROUP:
                    {
                        operation_kvitgroup(static_cast<indx> (req.numpar2));
                        break;
                    }
                    case OPERATION_KVIT_AGROUP:
                    {
                        operation_kvitagroup(static_cast<indx> (req.numpar2));
                        break;
                    }
                    case OPERATION_INCCOUNT:
                    {
                        operation_setcounter(static_cast<indx> (req.numpar2));
                        break;
                    }
                    case OPERATION_DECCOUNT:
                    {
                        operation_setcounter(static_cast<indx> (req.numpar2), false);
                        break;
                    }
                    case OPERATION_SET_VALID:
                    {
                        operation_setvalid(static_cast<indx> (req.numpar2), static_cast<vlvtype> (req.numpar3));
                        break;
                    }
                    case OPERATION_SET_INVALID:
                    {
                        operation_setvalid(static_cast<indx> (req.numpar2), static_cast<vlvtype> (req.numpar3));
                        break;
                    }
                    case OPERATION_SET_VALUE:
                    {
                        operation_setvalue(static_cast<indx> (req.numpar2), req.strpar1, static_cast<vlvtype> (req.numpar3));
                        break;
                    }
                    case OPERATION_SET_COMMAND:
                    {
                        operation_send_command(static_cast<indx> (req.numpar2), req.strpar1, req.numpar3 != 0);
                        break;
                    }
                    case SERVICE_OPEATION_START:
                    {
                        operation_startservice(static_cast<appidtype> (req.numpar2));
                        break;
                    }
                    case SERVICE_OPEATION_STOP:
                    {
                        operation_stopservice(static_cast<appidtype> (req.numpar2));
                        break;
                    }
                }
            }            catch (...) {
            }

            return RPC_OPERATION_RESP_ADMINOPERATION;
        }

        num16 adminintf::generate_impl(req_autorization& req, resp_autorization& resp) {
            try {
                clearerrors();
                resp.err = operation_autorizate(req.name, req.password);
            }            catch (...) {
            }
            return RPC_OPERATION_RESP_AUTORIZATION;
        }
    }
}
