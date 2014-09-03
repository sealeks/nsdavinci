/* 
 * File:   ClientmetaItemWraper.cpp
 * Author: Serg Alexeev sealeks@mail.ru
 * 
 * Created on 2 Февраль 2010 г., 17:54
 */

#include <admin/metawraper.h>
#include <admin/propertymanager.h>



namespace dvnci {
    namespace admin {

        using namespace std;

        bool inRangeVal(int val, int min, int max) {
            return ((val >= min) && (val <= max));
        }

        std::string valueFromSomeInt(int val, string tp = "1") {
            if (val != 0) return tp.c_str();
            else return "";
        }

        // ClientMetaItemWraper

        void basemetawraper::setValue(propidtype type_, indx id, string attribname_, std::string val, string def_tp, int min_, int max) {


            switch (type_) {
                case CMI_PROPERTY_TYPE_STR:
                {
                    _interface->meta(basetypeitem, id).property(attribname_, val);
                    break;
                };
                case CMI_PROPERTY_TYPE_INT:
                {
                    int val_;
                    if (str_to(val, val_)) _interface->meta(basetypeitem, id).property(attribname_, val);
                    break;
                }
                case CMI_PROPERTY_TYPE_UINT:
                {
                    unsigned int val_;
                    if (str_to(val, val_)) _interface->meta(basetypeitem, id).property(attribname_, val);
                    break;
                }
                case CMI_PROPERTY_TYPE_BOOL:
                {
                    bool val_;
                    if (str_to(val, val_))
                        _interface->meta(basetypeitem, id).property(attribname_, val);
                    break;
                }
                case CMI_PROPERTY_TYPE_DOUBLE:
                {
                    double val_;
                    if (str_to(val, val_)) _interface->meta(basetypeitem, id).property(attribname_, val);
                    break;
                }
            }
        }

        std::string basemetawraper::value(propidtype type_, indx id, string attribname_, string def_tp) {
            std::string tmp = _interface->meta(basetypeitem, id).property(attribname_);
            switch (type_) {
                case CMI_PROPERTY_TYPE_STR: return tmp;
                case CMI_PROPERTY_TYPE_INT: return (tmp != "") ? tmp: def_tp.c_str();
                case CMI_PROPERTY_TYPE_BOOL: return (tmp != "") ? tmp: def_tp.c_str();
                case CMI_PROPERTY_TYPE_DOUBLE: return (tmp != "") ? tmp: def_tp.c_str();
            }
            return "";
        }

        void basemetawraper::commit(indx id) {
            _interface->merge_entities(NT_MF_ROOT, id);
        }

        reparrrwraper::reparrrwraper(lcltype loc) : basemetawraper(loc) {
            propidtype propadd[] = {PROPERTY_NT_REPARR_NAME, PROPERTY_NT_REPARR_DELT, PROPERTY_NT_REPARR_GROUP, PROPERTY_NT_REPARR_WIDTH, PROPERTY_NT_REPARR_HEIGHT,
                PROPERTY_NT_REPARR_TYPE, PROPERTY_NT_REPARR_INITPER, PROPERTY_NT_REPARR_SUBPER, PROPERTY_NT_REPARR_AUTOPRINT, PROPERTY_NT_REPARR_AUTOCLOSE,
                PROPERTY_NT_REPARR_FOOTERSTR};
            addinpropertyset((propidtype*) & propadd, 11);
            basetypeitem = NT_MF_REPARR;
        }

        void reparrrwraper::addproprtyeditors_internal(abstractpropertymanager* mangr) {
            mangr->registpropertyeditor(PROPERTY_NT_REPARR_AUTOPRINT, &boolPrEdit);
            mangr->registpropertyeditor(PROPERTY_NT_REPARR_AUTOCLOSE, &boolPrEdit);
            mangr->registpropertyeditor(PROPERTY_NT_REPARR_FOOTERSTR, &boolPrEdit);
            mangr->registpropertyeditor(PROPERTY_NT_REPARR_INITPER, &boolPrEdit);
            mangr->registpropertyeditor(PROPERTY_NT_REPARR_SUBPER, &boolPrEdit);
            mangr->registpropertyeditor(PROPERTY_NT_REPARR_TYPE, &reptypePred);
        }

        void reparrrwraper::setProperty(indx id, propidtype prop, string val) {
            switch (prop) {
                case PROPERTY_NT_REPARR_NAME:
                {
                    setValue(CMI_PROPERTY_TYPE_STR, id, PROPERTY_NT_REPARR_NAME_STR, val);
                    break;
                };
                case PROPERTY_NT_REPARR_DELT:
                {
                    setValue(CMI_PROPERTY_TYPE_INT, id, PROPERTY_NT_REPARR_DELT_STR, val);
                    break;
                }
                case PROPERTY_NT_REPARR_GROUP:
                {
                    setValue(CMI_PROPERTY_TYPE_INT, id, PROPERTY_NT_REPARR_GROUP_STR, val);
                    break;
                }
                case PROPERTY_NT_REPARR_WIDTH:
                {
                    setValue(CMI_PROPERTY_TYPE_INT, id, PROPERTY_NT_REPARR_WIDTH_STR, val);
                    break;
                }
                case PROPERTY_NT_REPARR_HEIGHT:
                {
                    setValue(CMI_PROPERTY_TYPE_INT, id, PROPERTY_NT_REPARR_HEIGHT_STR, val);
                    break;
                }
                case PROPERTY_NT_REPARR_TYPE:
                {
                    setValue(CMI_PROPERTY_TYPE_INT, id, PROPERTY_NT_REPARR_TYPE_STR, val);
                    break;
                }
                case PROPERTY_NT_REPARR_INITPER:
                {
                    setValue(CMI_PROPERTY_TYPE_BOOL, id, PROPERTY_NT_REPARR_INITPER_STR, val);
                    break;
                }
                case PROPERTY_NT_REPARR_SUBPER:
                {
                    setValue(CMI_PROPERTY_TYPE_BOOL, id, PROPERTY_NT_REPARR_SUBPER_STR, val);
                    break;
                }
                case PROPERTY_NT_REPARR_AUTOPRINT:
                {
                    setValue(CMI_PROPERTY_TYPE_BOOL, id, PROPERTY_NT_REPARR_AUTOPRINT_STR, val);
                    break;
                }
                case PROPERTY_NT_REPARR_AUTOCLOSE:
                {
                    setValue(CMI_PROPERTY_TYPE_BOOL, id, PROPERTY_NT_REPARR_AUTOCLOSE_STR, val);
                    break;
                }
                case PROPERTY_NT_REPARR_FOOTERSTR:
                {
                    setValue(CMI_PROPERTY_TYPE_BOOL, id, PROPERTY_NT_REPARR_FOOTERSTR_STR, val);
                    break;
                }
            }
        }

        string reparrrwraper::getProperty(indx id, propidtype prop) {
            switch (prop) {
                case PROPERTY_NT_REPARR_NAME: return value(CMI_PROPERTY_TYPE_STR, id, PROPERTY_NT_REPARR_NAME_STR);
                case PROPERTY_NT_REPARR_DELT: return value(CMI_PROPERTY_TYPE_INT, id, PROPERTY_NT_REPARR_DELT_STR, "0");
                case PROPERTY_NT_REPARR_GROUP:return value(CMI_PROPERTY_TYPE_INT, id, PROPERTY_NT_REPARR_GROUP_STR, "0");
                case PROPERTY_NT_REPARR_WIDTH:return value(CMI_PROPERTY_TYPE_INT, id, PROPERTY_NT_REPARR_WIDTH_STR, "0");
                case PROPERTY_NT_REPARR_HEIGHT:return value(CMI_PROPERTY_TYPE_INT, id, PROPERTY_NT_REPARR_HEIGHT_STR, "0");
                case PROPERTY_NT_REPARR_TYPE: return value(CMI_PROPERTY_TYPE_INT, id, PROPERTY_NT_REPARR_TYPE_STR, "0");
                case PROPERTY_NT_REPARR_INITPER: return value(CMI_PROPERTY_TYPE_BOOL, id, PROPERTY_NT_REPARR_INITPER_STR, "0");
                case PROPERTY_NT_REPARR_SUBPER: return value(CMI_PROPERTY_TYPE_BOOL, id, PROPERTY_NT_REPARR_SUBPER_STR, "0");
                case PROPERTY_NT_REPARR_AUTOPRINT: return value(CMI_PROPERTY_TYPE_BOOL, id, PROPERTY_NT_REPARR_AUTOPRINT_STR, "0");
                case PROPERTY_NT_REPARR_AUTOCLOSE: return value(CMI_PROPERTY_TYPE_BOOL, id, PROPERTY_NT_REPARR_AUTOCLOSE_STR, "0");
                case PROPERTY_NT_REPARR_FOOTERSTR: return value(CMI_PROPERTY_TYPE_BOOL, id, PROPERTY_NT_REPARR_FOOTERSTR_STR, "0");
            }
            return "";
        }

        // ClientMetaRepHeaderItemWraper::

        repheaderwraper::repheaderwraper(lcltype loc) : basemetawraper(loc) {
            propidtype propadd[] = {PROPERTY_NT_REPHEADER_NAME, PROPERTY_NT_REPHEADER_COLOR,
                PROPERTY_NT_REPHEADER_TEXTCOLOR, PROPERTY_NT_REPHEADER_FONTSIZE};
            addinpropertyset((propidtype*) & propadd, 4);
            basetypeitem = NT_MF_REPHEADER;
        }

        void repheaderwraper::setProperty(indx id, propidtype prop, string val) {

            switch (prop) {
                case PROPERTY_NT_REPHEADER_NAME:
                {
                    setValue(CMI_PROPERTY_TYPE_STR, id, PROPERTY_NT_REPHEADER_NAME_STR, val);
                    break;
                };
                case PROPERTY_NT_REPHEADER_COLOR:
                {
                    setValue(CMI_PROPERTY_TYPE_STR, id, PROPERTY_NT_REPHEADER_COLOR_STR, val);
                    break;
                }
                case PROPERTY_NT_REPHEADER_TEXTCOLOR:
                {
                    setValue(CMI_PROPERTY_TYPE_STR, id, PROPERTY_NT_REPHEADER_TEXTCOLOR_STR, val);
                    break;
                }
                case PROPERTY_NT_REPHEADER_FONTSIZE:
                {
                    setValue(CMI_PROPERTY_TYPE_INT, id, PROPERTY_NT_REPHEADER_FONTSIZE_STR, val);
                    break;
                }
            }
        }

        string repheaderwraper::getProperty(indx id, propidtype prop) {

            switch (prop) {
                case PROPERTY_NT_REPHEADER_NAME: return value(CMI_PROPERTY_TYPE_STR, id, PROPERTY_NT_REPHEADER_NAME_STR);
                case PROPERTY_NT_REPHEADER_COLOR: return value(CMI_PROPERTY_TYPE_STR, id, PROPERTY_NT_REPHEADER_COLOR_STR, "0");
                case PROPERTY_NT_REPHEADER_TEXTCOLOR:return value(CMI_PROPERTY_TYPE_STR, id, PROPERTY_NT_REPHEADER_TEXTCOLOR_STR, "0");
                case PROPERTY_NT_REPHEADER_FONTSIZE:return value(CMI_PROPERTY_TYPE_INT, id, PROPERTY_NT_REPHEADER_FONTSIZE_STR, "0");
            }
            return "";
        }

        // ClientMetaUnitItemWraper::

        unitwraper::unitwraper(lcltype loc) : basemetawraper(loc) {
            propidtype propadd[] = {PROPERTY_NT_RUNIT_TG, PROPERTY_NT_RUNIT_SUMTYPE,
                PROPERTY_NT_RUNIT_ROUND, PROPERTY_NT_RUNIT_ROWCOLOR,
                PROPERTY_NT_RUNIT_TEXTCOLOR, PROPERTY_NT_RUNIT_NEGCOLOR};
            addinpropertyset((propidtype*) & propadd, 6);
            basetypeitem = NT_MF_UNIT;
        }

        void unitwraper::setProperty(indx id, propidtype prop, string val) {

            switch (prop) {
                case PROPERTY_NT_RUNIT_TG:
                {
                    setValue(CMI_PROPERTY_TYPE_STR, id, PROPERTY_NT_RUNIT_TG_STR, val);
                    break;
                };
                case PROPERTY_NT_RUNIT_SUMTYPE:
                {
                    setValue(CMI_PROPERTY_TYPE_INT, id, PROPERTY_NT_RUNIT_SUMTYPE_STR, val);
                    break;
                }
                case PROPERTY_NT_RUNIT_ROUND:
                {
                    setValue(CMI_PROPERTY_TYPE_INT, id, PROPERTY_NT_RUNIT_ROUND_STR, val);
                    break;
                }
                case PROPERTY_NT_RUNIT_ROWCOLOR:
                {
                    setValue(CMI_PROPERTY_TYPE_STR, id, PROPERTY_NT_RUNIT_ROWCOLOR_STR, val);
                    break;
                }
                case PROPERTY_NT_RUNIT_TEXTCOLOR:
                {
                    setValue(CMI_PROPERTY_TYPE_STR, id, PROPERTY_NT_RUNIT_TEXTCOLOR_STR, val);
                    break;
                }
                case PROPERTY_NT_RUNIT_NEGCOLOR:
                {
                    setValue(CMI_PROPERTY_TYPE_STR, id, PROPERTY_NT_RUNIT_NEGCOLOR_STR, val);
                    break;
                }
            }
        }

        string unitwraper::getProperty(indx id, propidtype prop) {

            switch (prop) {
                case PROPERTY_NT_RUNIT_TG: return value(CMI_PROPERTY_TYPE_STR, id, PROPERTY_NT_RUNIT_TG_STR);
                case PROPERTY_NT_RUNIT_SUMTYPE: return value(CMI_PROPERTY_TYPE_INT, id, PROPERTY_NT_RUNIT_SUMTYPE_STR, "0");
                case PROPERTY_NT_RUNIT_ROUND:return value(CMI_PROPERTY_TYPE_INT, id, PROPERTY_NT_RUNIT_ROUND_STR, "0");
                case PROPERTY_NT_RUNIT_ROWCOLOR:return value(CMI_PROPERTY_TYPE_STR, id, PROPERTY_NT_RUNIT_ROWCOLOR_STR);
                case PROPERTY_NT_RUNIT_TEXTCOLOR:return value(CMI_PROPERTY_TYPE_STR, id, PROPERTY_NT_RUNIT_TEXTCOLOR_STR);
                case PROPERTY_NT_RUNIT_NEGCOLOR:return value(CMI_PROPERTY_TYPE_STR, id, PROPERTY_NT_RUNIT_NEGCOLOR_STR);
            }
            return "";
        }

        void unitwraper::addproprtyeditors_internal(abstractpropertymanager* mangr) {
            mangr->registpropertyeditor(PROPERTY_NT_RUNIT_SUMTYPE, &repstatPred);
        }

        // ClientMetaTrendArrItemWraper::

        trendarrwraper::trendarrwraper(lcltype loc) : basemetawraper(loc) {
            propidtype propadd[] = {PROPERTY_NT_TRENDARR_NAME};
            addinpropertyset((propidtype*) & propadd, 1);
            basetypeitem = NT_MF_TRENDARR;
        }

        void trendarrwraper::setProperty(indx id, propidtype prop, string val) {

            switch (prop) {
                case PROPERTY_NT_TRENDARR_NAME:
                {
                    setValue(CMI_PROPERTY_TYPE_STR, id, PROPERTY_NT_TRENDARR_NAME_STR, val);
                    break;
                };
            }
        }

        string trendarrwraper::getProperty(indx id, propidtype prop) {

            switch (prop) {
                case PROPERTY_NT_TRENDARR_NAME: return value(CMI_PROPERTY_TYPE_STR, id, PROPERTY_NT_TRENDARR_NAME_STR);
            }
            return "";
        }

        // ClientMetaTrendHeaderItemWraper::

        trendheaderwraper::trendheaderwraper(lcltype loc) : basemetawraper(loc) {
            propidtype propadd[] = {PROPERTY_NT_TRENDHEADER_NAME};
            addinpropertyset((propidtype*) & propadd, 1);
            basetypeitem = NT_MF_TRENDHEADER;
        }

        void trendheaderwraper::setProperty(indx id, propidtype prop, string val) {

            switch (prop) {
                case PROPERTY_NT_TRENDHEADER_NAME:
                {
                    setValue(CMI_PROPERTY_TYPE_STR, id, PROPERTY_NT_TRENDHEADER_NAME_STR, val);
                    break;
                };
            }
        }

        string trendheaderwraper::getProperty(indx id, propidtype prop) {

            switch (prop) {
                case PROPERTY_NT_TRENDHEADER_NAME: return value(CMI_PROPERTY_TYPE_STR, id, PROPERTY_NT_TRENDHEADER_NAME_STR);
            }
            return "";
        }

        // ClientMetaTrendItemWraper::

        trendwraper::trendwraper(lcltype loc) : basemetawraper(loc) {
            propidtype propadd[] = {PROPERTY_NT_RTRENT_TG, PROPERTY_NT_RTRENT_HEIGHT, PROPERTY_NT_RTRENT_WIDTH, PROPERTY_NT_RTRENT_FILL,
                PROPERTY_NT_RTRENT_PENCOLOR, PROPERTY_NT_RTRENT_FILLCOLOR};
            addinpropertyset((propidtype*) & propadd, 6);
            basetypeitem = NT_MF_TREND;
        }

        void trendwraper::addproprtyeditors_internal(abstractpropertymanager* mangr) {
            mangr->registpropertyeditor(PROPERTY_NT_RTRENT_FILL, &boolPrEdit);
        }

        void trendwraper::setProperty(indx id, propidtype prop, string val) {

            switch (prop) {
                case PROPERTY_NT_RTRENT_TG:
                {
                    setValue(CMI_PROPERTY_TYPE_STR, id, PROPERTY_NT_RUNIT_TG_STR, val);
                    break;
                };
                case PROPERTY_NT_RTRENT_HEIGHT:
                {
                    setValue(CMI_PROPERTY_TYPE_INT, id, PROPERTY_NT_RTRENT_HEIGHT_STR, val);
                    break;
                }
                case PROPERTY_NT_RTRENT_WIDTH:
                {
                    setValue(CMI_PROPERTY_TYPE_INT, id, PROPERTY_NT_RTRENT_WIDTH_STR, val);
                    break;
                }
                case PROPERTY_NT_RTRENT_FILL:
                {
                    setValue(CMI_PROPERTY_TYPE_STR, id, PROPERTY_NT_RTRENT_FILL_STR, val);
                    break;
                }
                case PROPERTY_NT_RTRENT_PENCOLOR:
                {
                    setValue(CMI_PROPERTY_TYPE_STR, id, PROPERTY_NT_RTRENT_PENCOLOR_STR, val);
                    break;
                }
                case PROPERTY_NT_RTRENT_FILLCOLOR:
                {
                    setValue(CMI_PROPERTY_TYPE_STR, id, PROPERTY_NT_RTRENT_FILLCOLOR_STR, val);
                    break;
                }
            }
        }

        string trendwraper::getProperty(indx id, propidtype prop) {

            switch (prop) {
                case PROPERTY_NT_RTRENT_TG: return value(CMI_PROPERTY_TYPE_STR, id, PROPERTY_NT_RUNIT_TG_STR);
                case PROPERTY_NT_RTRENT_HEIGHT: return value(CMI_PROPERTY_TYPE_INT, id, PROPERTY_NT_RTRENT_HEIGHT_STR, "0");
                case PROPERTY_NT_RTRENT_WIDTH:return value(CMI_PROPERTY_TYPE_INT, id, PROPERTY_NT_RTRENT_WIDTH_STR, "0");
                case PROPERTY_NT_RTRENT_FILL:return value(CMI_PROPERTY_TYPE_STR, id, PROPERTY_NT_RTRENT_FILL_STR);
                case PROPERTY_NT_RTRENT_PENCOLOR:return value(CMI_PROPERTY_TYPE_STR, id, PROPERTY_NT_RTRENT_PENCOLOR_STR);
                case PROPERTY_NT_RTRENT_FILLCOLOR:return value(CMI_PROPERTY_TYPE_STR, id, PROPERTY_NT_RTRENT_FILLCOLOR_STR);
            }
            return "";
        }


        // ClientMetaMessageArrItemWraper::

        messagearrwraper::messagearrwraper(lcltype loc) : basemetawraper(loc) {
            propidtype propadd[] = {PROPERTY_NT_MESSARR_NAME};
            addinpropertyset((propidtype*) & propadd, 1);
            basetypeitem = NT_MF_MESSARR;
        }

        void messagearrwraper::setProperty(indx id, propidtype prop, string val) {

            switch (prop) {
                case PROPERTY_NT_MESSARR_NAME:
                {
                    setValue(CMI_PROPERTY_TYPE_STR, id, PROPERTY_NT_MESSARR_NAME_STR, val);
                    break;
                };
            }
        }

        string messagearrwraper::getProperty(indx id, propidtype prop) {
            switch (prop) {
                case PROPERTY_NT_MESSARR_NAME: return value(CMI_PROPERTY_TYPE_STR, id, PROPERTY_NT_MESSARR_NAME_STR);
            }
            return "";
        }

        // ClientMetaMessageHeaderItemWraper::

        messageheaderwraper::messageheaderwraper(lcltype loc) : basemetawraper(loc) {
            propidtype propadd[] = {PROPERTY_NT_MESSHEADER_NAME};
            addinpropertyset((propidtype*) & propadd, 1);
            basetypeitem = NT_MF_MESSHEADER;
        }

        void messageheaderwraper::setProperty(indx id, propidtype prop, string val) {

            switch (prop) {
                case PROPERTY_NT_MESSHEADER_NAME:
                {
                    setValue(CMI_PROPERTY_TYPE_STR, id, PROPERTY_NT_MESSHEADER_NAME_STR, val);
                    break;
                };
            }
        }

        string messageheaderwraper::getProperty(indx id, propidtype prop) {

            switch (prop) {
                case PROPERTY_NT_MESSHEADER_NAME: return value(CMI_PROPERTY_TYPE_STR, id, PROPERTY_NT_MESSHEADER_NAME_STR);
            }
            return "";
        }

        // ClientMetaMessageItemWraper::

        messagewraper::messagewraper(lcltype loc) : basemetawraper(loc) {
            propidtype propadd[] = {PROPERTY_NT_RMESSAGE_TG};
            addinpropertyset((propidtype*) & propadd, 1);
            basetypeitem = NT_MF_MESSAGE;
        }

        void messagewraper::setProperty(indx id, propidtype prop, string val) {

            switch (prop) {
                case PROPERTY_NT_RMESSAGE_TG:
                {
                    setValue(CMI_PROPERTY_TYPE_STR, id, PROPERTY_NT_RMESSAGE_TG_STR, val);
                    break;
                };
            }
        }

        std::string messagewraper::getProperty(indx id, propidtype prop) {

            switch (prop) {
                case PROPERTY_NT_RMESSAGE_TG: return value(CMI_PROPERTY_TYPE_STR, id, PROPERTY_NT_RMESSAGE_TG_STR);
            }
            return "";
        }



        // ClientMetaMetaItemWraper::

        metawraper::metawraper(lcltype loc) : basemetawraper(loc) {
            propidtype propadd[] = {PROPERTY_NT_META_PROVIDER, PROPERTY_NT_META_CONSTR, PROPERTY_NT_META_HOST};
            addinpropertyset((propidtype*) & propadd, 3);
            basetypeitem = NT_MF_ROOT;
        }

        void metawraper::addproprtyeditors_internal(abstractpropertymanager* mangr) {
            mangr->registpropertyeditor(PROPERTY_NT_META_PROVIDER, &dbprovPred);
        }

        void metawraper::setProperty(indx id, propidtype prop, string val) {

            switch (prop) {
                case PROPERTY_NT_META_PROVIDER:
                {
                    setValue(CMI_PROPERTY_TYPE_STR, id, PROPERTY_NT_META_PROVIDER_STR, val);
                    break;
                };
                case PROPERTY_NT_META_CONSTR:
                {
                    setValue(CMI_PROPERTY_TYPE_STR, id, PROPERTY_NT_META_CONSTR_STR, val);
                    break;
                }
                case PROPERTY_NT_META_HOST:
                {
                    setValue(CMI_PROPERTY_TYPE_STR, id, PROPERTY_NT_META_HOST_STR, val);
                    break;
                }
            }
        }

        std::string metawraper::getProperty(indx id, propidtype prop) {

            switch (prop) {
                case PROPERTY_NT_META_PROVIDER: return value(CMI_PROPERTY_TYPE_STR, id, PROPERTY_NT_META_PROVIDER_STR);
                case PROPERTY_NT_META_CONSTR:return value(CMI_PROPERTY_TYPE_STR, id, PROPERTY_NT_META_CONSTR_STR);
                case PROPERTY_NT_META_HOST:return value(CMI_PROPERTY_TYPE_STR, id, PROPERTY_NT_META_HOST_STR);
            }
            return "";
        }
    }
}

