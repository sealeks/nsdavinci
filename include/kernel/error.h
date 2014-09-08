/* 
 * File:   error
 * Author: Serg Alexeev sealeks@mail.ru
 *
 * Created on 12 Ноябрь 2009 г., 18:37
 */

#ifndef _DVNCI_KRNL_NS_ERROR_H
#define	_DVNCI_KRNL_NS_ERROR_H

#include <kernel/constdef.h>

namespace dvnci {


    //  < 0x100  предупреждения и уведомления


    // remote inf error
    const ns_error NS_ERROR_SUCCESS = 0;
    // неизвестная ошибка
    const ns_error NS_ERROR_NODEF = 0x100;
    // не найден главный файл проекта
    const ns_error NS_ERROR_MAPMEMORY = 0x300;
    // не найден главный файл проекта
    const ns_error NS_ERROR_MAINFILENOTFOUND = 0x301;
    // некорректный ответ
    const ns_error NS_ERROR_ERRRESP = 0x400;
    // ошибочная операция 
    const ns_error NS_ERROR_ENTITY_OPERATE = 0x10E;
    // новый объект не может быть размещен в разделяемой памяти, необходим ремапинг объектов памяти
    const ns_error RESERV_MEMSHARE_EXTEND = 0x10F;
    // строка слишком длинна
    const ns_error NS_ERROR_STRING_LONG = 0x11A;
    // нет родителя объекта
    const ns_error NS_ERROR_NOPARENT = 0x11B;
    // конфликт версий удаленного интерфейса
    const ns_error REMOTE_VERSION_CONFLICT = 0x110;
    // невозможно развязать проект
    const ns_error REMOTE_NOMAP_PROJECT = 0x111;
    // имя новой или переназываемой сущности дублирует существующее
    const ns_error ERROR_NAMEENTETY_DUBLICATE = 0x112;
    // имя новой или переназываемой сущности некорректно
    const ns_error ERROR_NAMEENTETY_CORRECT = 0x113;
    // не существует родительской сущности
    const ns_error ERROR_PARENTENTETY_CORRECT = 0x115;
    // родительскaя сущность не может быть удалена так как нeпуста
    const ns_error ERROR_ENTETYREMOVE_ISNOEMTY = 0x116;
    // тип не может быть установлен, уже существует (для экcлюзивных)
    const ns_error ERROR_ENTETYNOGHANETYPE_ISEXCLUSIVE = 0x117;
    // потеряна связь с удаленной службой
    const ns_error ERROR_FAILNET_CONNECTED = 0x118;
    // не установлена связь с удаленной службой
    const ns_error ERROR_NONET_CONNECTED = 0x119;
    // не установлена связь с интерфесом
    const ns_error ERROR_NOINTF_CONNECTED = 0x120;
    // объект не может клонироаться
    const ns_error ERROR_NO_CLONE = 0x121;
    // сущность не существует
    const ns_error ERROR_ENTNOEXIST = 0x122;
    // тег не существует
    const ns_error ERROR_TAGNOEXIST = 0x200;
    // ошибка парсинга выражения
    const ns_error ERROR_EXPRPARSE = 0x201;
    // ошибочная операция
    const ns_error ERROR_EXPROPERATOR = 0x202;
    // выражение не проинициализировано
    const ns_error ERROR_EXPRNOINIT = 0x203;
    // математическая ошибка при вычислении
    const ns_error ERROR_EXPRMATH = 0x204;
    // интерфейс не инициализирован
    const ns_error ERROR_NILLINF = 0x205;
    // авторизация не пройдена
    const ns_error ERROR_AUTORIZATION_FAIL = 0x206;
    // база не найдена
    const ns_error ERROR_BASENOTFOUND = 0x207;
    // тип не обрабатывается
    const ns_error ERROR_TYPENOPROCCESS = 0x208;
    // ошибка привязки
    const ns_error ERROR_BINDING = 0x209;
    // нет данных
    const ns_error ERROR_NODATA = 0x20A;
    // группа не существует
    const ns_error ERROR_GROUPNOEXIST = 0x20B;
    // тег не найден на удаленном сервере
    const ns_error ERROR_NOFIND_REMOTEITEM = 0x20C;
    // тип тега не может быть приведен к требуемому
    const ns_error ERROR_TYPENOCAST = 0x20D;
    // пустой ответ
    const ns_error ERROR_NULLRESPONSE = 0x20E;
    // источник занят, необходимо подождать
    const ns_error ERROR_SOURSEBUSY = 0x20F;
    // задание удалено по таймауту
    const ns_error ERROR_TASKTIMEOUT = 0x210;
    // канал не определен
    const ns_error ERROR_IO_DEVICE_CHANAL_NOT_DEF = 0x420;
    // таймут истек
    const ns_error ERROR_IO_TIMOUT_EXPIRE = 0x421;
    // таймут истек
    const ns_error ERROR_IO_CHANNOOPEN = 0x422;
    // таймут истек
    const ns_error ERROR_IO_NOSETOPTION = 0x423;
    // связь установлена, но протокол не инициализирован
    const ns_error ERROR_IO_NOINIT_PROTOCOL = 0x424;
    // тип канала не поддерживается серером или пуст
    const ns_error ERROR_IO_LINK_NOT_SUPPORT = 0x425;
    // нет соединения с устройством
    const ns_error ERROR_IO_LINK_NOT_CONNECTION = 0x426;
    // ошибка контрольной суммы
    const ns_error ERROR_IO_CRC = 0x427;
    // ошибка ответа устройства
    const ns_error ERROR_IO_PARSERESP = 0x428;
    // ошибка парсинга ответа устройства
    const ns_error ERROR_IO_NO_PARSEDATA = 0x429;
    // зависание сервиса ввода вывода
    const ns_error ERROR_IO_SERVICE_LOCK = 0x430;
    // ошибка генерации запроса к устройству
    const ns_error ERROR_IO_NO_GENERATE_REQ = 0x431;
    // ошибка адреса устройства
    const ns_error ERROR_IO_NO_CORRECT_ADDR = 0x432;
    // ошибка рассхинхронизации настроек канала
    const ns_error ERROR_IO_NOSYNC_LINK = 0x433;
    // ошибка инициализации генератора блока
    const ns_error ERROR_IO_NOBLOCKGEN_LINK = 0x434;
    // ошибка инициализации менеджера устройств
    const ns_error ERROR_IO_NODEVMANAGER_LINK = 0x435;
    // не инициализирова поток ввода ввывода
    const ns_error ERROR_IO_NOLINKSTREAM = 0x436;
    // ошибка адресации MODBUS или другая
    const ns_error ERROR_IO_MODBUS_ERR = 0x437;
    // устройство ответило NAK
    const ns_error ERROR_IO_DEVICE_NAK = 0x438;
    // пустой ответ
    const ns_error ERROR_IO_NO_DATA = 0x439;
    // ошибка преобразования
    const ns_error ERROR_IO_DATA_CONV = 0x43A;
    // нет соединения с базой данных
    const ns_error ERROR_NO_DATABASE_CONN = 0x440;
    // ошибка при выполнении запроса с базой данных
    const ns_error ERROR_DATABASE_EXEC = 0x441;
    // ошибка при выполнении запроса с базой данных
    const ns_error ERROR_PROTOCOL_SEQ = 0x442;
    // ошибка при выполнении запроса с базой данных
    const ns_error ERROR_PROTOCOL_ERROR = 0x443;
    
    const ns_error ERROR_DATA_OUT_OF_RANGE = 0x450;    

    // DATABASE error

    // нет соединения
    const ns_error ERROR_DB_NOCONNECTION = 0x801;
    // разрыв соединения
    const ns_error ERROR_DB_REFUSECONNECTION = 0x802;
    // неизвестная ошибка
    const ns_error ERROR_DB_NODEF = 0x803;
    // провайдер не опредеолен или не поддерживается
    const ns_error ERROR_DB_NOPROVIDER = 0x804;
    // ошибка авторизации
    const ns_error ERROR_DB_AUTH = 0x806;
    // неверный запрос
    const ns_error ERROR_DB_SQLREQ = 0x808;
    // нет файла описания
    const ns_error ERROR_DB_NOTRENDDEF = 0x809;
    // не  найденн индекс для тега
    const ns_error ERROR_DB_NOINDEX = 0x80A;

    inline ns_error dvn_error(const ns_error& val) {
        return val > 0xFF ? val : 0;
    }

    inline ns_error dvn_warning(const ns_error& val) {
        return val < 0x100 ? val : 0;
    }


    class dvncierror;

    typedef std::pair<int, dvncierror> int_dvncierror_pair;
    typedef std::map<int, dvncierror, std::less<int>, std::allocator<int_dvncierror_pair > > int_dvncierror_map;

    class dvncierror {

    public:

        dvncierror(ns_error cod = 0, std::string _str_ = "", indx _key_ = 0) {
            str_ = _str_;
            key_ = _key_;
            code_ = cod;
        }

        ~dvncierror() {
        }

        std::string str() const {
            return str_;
        }

        void str(const std::string& val) {
            str_ = val;
        }

        ns_error code() const {
            return code_;
        }

        indx key() const {
            return key_;
        }

        operator bool() const {
            return code_;
        }

        std::ostream & operator<<(std::ostream& os) {
            return os << "code=" << code_ << " , str=" << str_ << ", key=" << key_ << std::endl;
        }

        friend std::ostream & operator<<(std::ostream& os, dvncierror& ns) {
            return os << "code=" << ns.code_ << " , str=" << ns.str_ << ", key=" << ns.key_ << std::endl;
        }
    private:
        std::string str_;
        indx key_;
        ns_error code_;
    };
}

#endif	/* _NS_ERROR_H */

