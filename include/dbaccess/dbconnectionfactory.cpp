
#include <dbaccess/dbconnectionfactory.h>
#include <dbaccess/dbpsgrdriver.h>

namespace dvnci {
    namespace database {

        using namespace soci;

        dbdriver_ptr bdconnectionfactory::build(dvnci::num32 provider, std::string constr, bool ex_write) {
            switch (provider) {

                case dvnci::PROPERTY_DB_PROVIDER_POSTGRESS: return dbdriver_ptr(new dbpsgrdriver(constr, ex_write));
                    // case PROPERTY_DB_PROVIDER_ORACLE:
                    /* case PROPERTY_DB_PROVIDER_MYSQL:*/
            }
            return dbdriver_ptr();}}}