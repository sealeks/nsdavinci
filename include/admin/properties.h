/* 
 * File:   properties_name.h
 * Author: Serg Alexeev sealeks@mail.ru
 *
 * Created on 22 Ноябрь 2009 г., 21:33
 */

#ifndef _ADMININTF_ADMINPROPERTIES__H
#define	_ADMININTF_ADMINPROPERTIES__H

#include <kernel/constdef.h>

namespace dvnci{
namespace admin{

typedef int propedittype;

// типы отображения свойств
const propedittype TYPE_PE_DEFAULT=0x0;
const propedittype TYPE_PE_NOTEDIT=0x1;
const propedittype TYPE_PE_CHECKED=0x2;
const propedittype TYPE_PE_LIST=0x3;
const propedittype TYPE_PE_BUTTON=0x4;


// Базовые свойсва тегов и групп
const propidtype PROPERTY_CNFG_ROOT=0x10;
const propidtype PROPERTY_CNFG_PATH=0x11;
const propidtype PROPERTY_CNFG_NAME=0x12;
const propidtype PROPERTY_CNFG_COMMENT=0x13;
const propidtype PROPERTY_CNFG_OSTYPE=0x14;
const propidtype PROPERTY_CNFG_MAPSIZE=0x15;
const propidtype PROPERTY_CNFG_DBMANAGER=0x16;
const propidtype PROPERTY_CNFG_DBCONSTR=0x17;
const propidtype PROPERTY_CNFG_ANALOGBUFF=0x18;
const propidtype PROPERTY_CNFG_HISTORYPERIOD=0x19;
const propidtype PROPERTY_CNFG_LOGLEVEL=0x1A;
const propidtype PROPERTY_CNFG_ADMINNAME=0x1B;
const propidtype PROPERTY_CNFG_ADMINPASS=0x1C;
const propidtype PROPERTY_CNFG_ADMINPORT=0x1D;
const propidtype PROPERTY_CNFG_REMOTEPORT=0x1E;
const propidtype PROPERTY_CNFG_OPCREMOTEPORT=0x1F;

const propidtype PROPERTY_NAME_SERVICE=0x080;
const propidtype PROPERTY_PATH_SERVICE=0x082;
const propidtype PROPERTY_STARTTYPE_SERVICE=0x084;
const propidtype PROPERTY_TYPE_SERVICE=0x086;
const propidtype PROPERTY_STATUS_SERVICE=0x08F;

const propidtype PROPERTY_NAME_TAG=0x0100;
const propidtype PROPERTY_NAME_GROUP=0x0101;
const propidtype PROPERTY_ENUM_GROUP=0x0102;
const propidtype PROPERTY_NAME_ALARMGROUP=0x0105;
const propidtype PROPERTY_NAME_USER=0x0110;
const propidtype PROPERTY_NAME_USERPASSWORD=0x0112;
const propidtype PROPERTY_NAME_USERLEVEL=0x0114;
const propidtype PROPERTY_ACCESSRULENAME = 0x120;
const propidtype PROPERTY_ACCESSRULEAPP = 0x121;
const propidtype PROPERTY_ACCESSRULECIDR = 0x122;
const propidtype PROPERTY_ACCESSRULEAPPID = 0x123;
const propidtype PROPERTY_ACCESSRULERULE= 0x124;
const propidtype PROPERTY_ACCESSRULELEV = 0x125;
const propidtype PROPERTY_TYPE_TAG=0x0150;
const propidtype PROPERTY_TYPE_GROUP=0x0151;
const propidtype PROPERTY_CHANALTYPE_GROUP=0x0261;
const propidtype PROPERTY_LGK_CHANALTYPE_GROUP=0x0262;
const propidtype PROPERTY_MDB_CHANALTYPE_GROUP=0x0263;
const propidtype PROPERTY_KOYO_CHANALTYPE_GROUP=0x0264;
const propidtype PROPERTY_CHANALNUM_GROUP=0x0361;
const propidtype PROPERTY_CHANALHOST_GROUP=0x0371;
const propidtype PROPERTY_CHANALHOST_ADDR_GROUP=0x0373;
const propidtype PROPERTY_MODBUS_PROTOCOL=0x0381;
const propidtype PROPERTY_LGK_PROTOCOL=0x0382;
const propidtype PROPERTY_KOYO_PROTOCOL=0x0383;
const propidtype PROPERTY_CHANALPORT_GROUP=0x0461;
const propidtype PROPERTY_IPv4ADDRES_GROUP=0x0363;
const propidtype PROPERTY_IPv6ADDRES_GROUP=0x0364;
const propidtype PROPERTY_RSNUM_GROUP=0x0365;
const propidtype PROPERTY_DEVNUM_GROUP=0x0462;
const propidtype PROPERTY_CHANALUSER_GROUP=0x0471;
const propidtype PROPERTY_OPCNAME_GROUP=0x0373;
const propidtype PROPERTY_DDESERVER_NAME=0x0375;
const propidtype PROPERTY_DDESERVER_TOPIC=0x0377;
const propidtype PROPERTY_OPCGROUP_GROUP=0x0472;
const propidtype PROPERTY_OPCVER_GROUP=0x0474;
const propidtype PROPERTY_OPCCONTYPE_GROUP=0x0476;
const propidtype PROPERTY_OPCUSEHDA_GROUP=0x0478;

const propidtype PROPERTY_RS232_BOUNDRATE=0x0482;
const propidtype PROPERTY_RS232_DATABIT=0x0484;
const propidtype PROPERTY_RS232_STOPBIT=0x0486;
const propidtype PROPERTY_RS232_PARITY=0x0487;
const propidtype PROPERTY_RS232_FLOWCTRL=0x0488;
const propidtype PROPERTY_RS232_FLOWCTRLAF=0x0489;
const propidtype PROPERTY_RS232_FLOWCTRLBE=0x048A;
const propidtype PROPERTY_RS232_RI=0x048B;
const propidtype PROPERTY_RS232_RTM=0x048C;
const propidtype PROPERTY_RS232_RTC=0x048D;
const propidtype PROPERTY_RS232_WTM=0x048E;
const propidtype PROPERTY_RS232_WTC=0x048F;

const propidtype PROPERTY_GR_TO=    0x0563;
const propidtype PROPERTY_GR_DB=    0x0565;
const propidtype PROPERTY_GR_GR=    0x0567;
const propidtype PROPERTY_GR_SYNCT= 0x0569;
const propidtype PROPERTY_GR_BS=    0x056B;
const propidtype PROPERTY_GR_ABS=   0x056C;
const propidtype PROPERTY_GR_TCNT=  0x056D;
const propidtype PROPERTY_GR_INDTO=  0x056F;
const propidtype PROPERTY_GR_LOCALE=  0x0580;
const propidtype PROPERTY_CHANALPASSWORD_GROUP=0x0481;
const propidtype PROPERTY_COMMENT_TAG=0x0200;
const propidtype PROPERTY_EVENTTEXT_TAG=0x0250;
const propidtype PROPERTY_BIND_TAG=0x0300;
const propidtype PROPERTY_VAL_TAG=0x0350;
const propidtype PROPERTY_RANGABLE_TAG=0x390;
const propidtype PROPERTY_MINCONT_TAG=0x0400;
const propidtype PROPERTY_PREDCOUNT_TAG=0x0401;
const propidtype PROPERTY_MAXCONT_TAG=0x00500;
const propidtype PROPERTY_DELTCOUNT_TAG=0x0501;
const propidtype PROPERTY_REPSTATISIC_TAG=0x0502;
const propidtype PROPERTY_SERVERDB_TAG=0x00600;
const propidtype PROPERTY_UEMIN_TAG=0x0700;
const propidtype PROPERTY_UEMAX_TAG=0x0800;
const propidtype PROPERTY_UETEXT_TAG=0x0900;
const propidtype PROPERTY_OFFMSG_TAG=0x0A00;
const propidtype PROPERTY_OFFMSGTEXT_TAG=0x0B00;
const propidtype PROPERTY_ONMSG_TAG=0x0B50;
const propidtype PROPERTY_ONMSGTEXT_TAG=0x0BA0;
const propidtype PROPERTY_ALARMMSG_TAG=0x0C00;
const propidtype PROPERTY_ALARMLEVEL_TAG=0x0C01;
const propidtype PROPERTY_AVARMSG_TAG=0x0D00;
const propidtype PROPERTY_ALARMMSGTEXT_TAG=0x0E00;
const propidtype PROPERTY_ALARMVAL_TAG=0x0F00;
const propidtype PROPERTY_ALARMVALBOOL_TAG=0x0F01;
const propidtype PROPERTY_ALARMCASE_TAG=0x1000;
const propidtype PROPERTY_ALARMCASEBOOL_TAG=0x1001;
const propidtype PROPERTY_ARCH_TAG=0x1100;
const propidtype PROPERTY_ARCHDB_TAG=0x1200;
const propidtype PROPERTY_RW_TAG=0x1250;
const propidtype PROPERTY_AL_TAG=0x1260;
const propidtype PROPERTY_ALWACTIVE_TAG=0x1280;
const propidtype PROPERTY_TAG_TYPE=0x1300;

const propidtype PROPERTY_ALARMCASE_TAG_LESS=0x0000;
const propidtype PROPERTY_ALARMCASE_TAG_MORE=0x0001;
const propidtype PROPERTY_ALARMCASE_TAG_EQUAL=0x0002;

const propidtype PROPERTY_ALARMLEVEL_NONE=0x0;
const propidtype PROPERTY_ALARMLEVEL_NONICE=0x1;
const propidtype PROPERTY_ALARMLEVEL_WARNING=0x2;
const propidtype PROPERTY_ALARMLEVEL_ACCIDENT=0x3;



// clientmeta properties


//<meta>
//<meta DBProvider="1" constring="server=localhost;database=trend;user=postgres;password=1324;" host="home">
const propidtype PROPERTY_NT_META_PROVIDER=0x6000;  //DBProvider
const propidtype PROPERTY_NT_META_CONSTR=0x6010;  //constring
const propidtype PROPERTY_NT_META_HOST=0x6020;  //host



// <ReportHeader>
//<ReportHeader key="0" color="" fontsize="" name="Газ" textcolor="">
const propidtype PROPERTY_NT_REPHEADER_NAME=0x4300;  //name
const propidtype PROPERTY_NT_REPHEADER_COLOR=0x4310;  //color
const propidtype PROPERTY_NT_REPHEADER_TEXTCOLOR=0x4320;  //textcolor
const propidtype PROPERTY_NT_REPHEADER_FONTSIZE=0x4330;  //fontsize


// <ReportArr>
// expl <ReportArr key="0" delt="0" group="1" height="250" name="Часовые расходы " sum="1" type="4" width="100" initperiod="" subperiod="" autoprpropidtype="" autoclose="">
const propidtype PROPERTY_NT_REPARR_NAME=0x4000;  //name
const propidtype PROPERTY_NT_REPARR_DELT=0x4010;  //delt
const propidtype PROPERTY_NT_REPARR_GROUP=0x4020;  //group
const propidtype PROPERTY_NT_REPARR_WIDTH=0x4030;  //width
const propidtype PROPERTY_NT_REPARR_HEIGHT=0x4040;  //height
const propidtype PROPERTY_NT_REPARR_TYPE=0x4050;  //type
const propidtype PROPERTY_NT_REPARR_INITPER=0x4060;  //initperiod
const propidtype PROPERTY_NT_REPARR_SUBPER=0x4070;  //subperiod
const propidtype PROPERTY_NT_REPARR_AUTOPRINT=0x4080;  //autoprint
const propidtype PROPERTY_NT_REPARR_AUTOCLOSE=0x4090;  //autoclose
const propidtype PROPERTY_NT_REPARR_FOOTERSTR=0x4100;  //autoclose


// <unit>
//<unit key="19" round="0" sumtype="1" tg="FT61_18_h" rowcolor="" textcolor="" negcolor=""/>

const propidtype PROPERTY_NT_RUNIT_TG=0x4400;  //tg
const propidtype PROPERTY_NT_RUNIT_SUMTYPE=0x4410;  //sumtype
const propidtype PROPERTY_NT_RUNIT_ROUND=0x4420;  //round
const propidtype PROPERTY_NT_RUNIT_ROWCOLOR=0x4430;  //rowcolor
const propidtype PROPERTY_NT_RUNIT_TEXTCOLOR=0x4440;  //textcolor
const propidtype PROPERTY_NT_RUNIT_NEGCOLOR=0x4450;  //negcolor

// <TrendHeader>
//<TrendHeader key="0" name="Газ">
const propidtype PROPERTY_NT_TRENDHEADER_NAME=0x5000;  //name

// <TrendArr>
// <TrendArr key="1" name="Расходы">
const propidtype PROPERTY_NT_TRENDARR_NAME=0x5100;  //name

// <trend>
//<trend key="0" fill="" fillcolor="" height="320" pencolor="666600" tg="FE1" width="650" />
const propidtype PROPERTY_NT_RTRENT_TG=0x5200;  //tg
const propidtype PROPERTY_NT_RTRENT_HEIGHT=0x5210;  //height
const propidtype PROPERTY_NT_RTRENT_WIDTH=0x5220;  //width
const propidtype PROPERTY_NT_RTRENT_FILL=0x5230;  //fill
const propidtype PROPERTY_NT_RTRENT_PENCOLOR=0x5240;  //pencolor
const propidtype PROPERTY_NT_RTRENT_FILLCOLOR=0x5250;  //fillcolor

// <MessageHeader>
//<MessageHeader key="0" name="Газ">
const propidtype PROPERTY_NT_MESSHEADER_NAME=0x5500;  //name

// <MessageArr>
// <MessageArr key="1" name="Расходы">
const propidtype PROPERTY_NT_MESSARR_NAME=0x5600;  //name

// <message>
//<message key="0" tg="FE1"  />
const propidtype PROPERTY_NT_RMESSAGE_TG=0x5700;  //tg

}
}

#endif	/* _PROPERTIES_NAME_H */

