/* 
 * File:   iec60870_detail.cpp
 * Author: Alexeev
 */

#include <iec60870/iec60870_detail.h>



namespace prot80670 {

    void millisec_to_now(boost::xtime& xt, std::size_t milsec) {
        boost::xtime_get(&xt, boost::TIME_UTC_);
        xt.sec += milsec / 1000;
        if ((xt.nsec + (milsec % 1000) * 1000000) < 1000000000) {
            xt.nsec += (milsec % 1000) * 1000000;
        } else {
            xt.sec += 1;
            xt.nsec += ((milsec % 1000) * 1000000 + xt.nsec - 1000000000);
        }
    }

    std::string rs_name(chanalnum_type vl) {
#if defined(_IEC60870_WIN_) 
        return "\\\\.\\COM" + to_str(vl);
#elif defined(_IEC60870_LIN_)
        return "/dev/ttyS" + to_str(vl ? (vl - 1) : 0);
#endif                     
    }

#if defined(_IEC60870_WIN_)        

    void set_com_baudrate(com_port_option_type& opt, const baudrate_type& br) {
        opt.BaudRate = static_cast<DWORD> (br);
    }

    void set_com_comoption(com_port_option_type& opt, size_t databit, const rsparity_type& prt, const rsstopbit_type& stpbt) {
        opt.ByteSize = static_cast<BYTE> (databit);
        opt.Parity = static_cast<BYTE> (prt);
        opt.StopBits = static_cast<BYTE> (stpbt);
    }

    void set_com_cominill(com_port_option_type& opt) {
        opt.fOutxCtsFlow = 0;
        opt.fOutxDsrFlow = 0;
        opt.fDtrControl = 0;
        opt.fDsrSensitivity = 0;
        opt.fOutX = 0;
        opt.fInX = 0;
    }

    void set_com_flowcontrol(com_port_option_type& opt, bool vl) {
        if (!vl) {
            opt.fOutxCtsFlow = 0;
            opt.fOutxDsrFlow = 0;
            opt.fDtrControl = 0;
            opt.fDsrSensitivity = 0;
            opt.fOutX = 0;
            opt.fInX = 0;
        } else {
            opt.fOutxCtsFlow = 0;
            opt.fOutxDsrFlow = 0;
            opt.fDtrControl = 0;
            opt.fDsrSensitivity = 0;
            opt.fOutX = 0;
            opt.fInX = 0;
        }
    }

#elif defined(_IEC60870_LIN_)

    void set_com_baudrate(com_port_option_type& opt, const baudrate_type& br) {
        switch (br) {
            case IEC870_BAUNDRATE_110:
            {
                cfsetospeed(&opt, B110);
                cfsetispeed(&opt, B110);
                return;
            }
            case IEC870_BAUNDRATE_300:
            {
                cfsetospeed(&opt, B300);
                cfsetispeed(&opt, B300);
                return;
            }
            case IEC870_BAUNDRATE_600:
            {
                cfsetospeed(&opt, B600);
                cfsetispeed(&opt, B600);
                return;
            }
            case IEC870_BAUNDRATE_1200:
            {
                cfsetospeed(&opt, B1200);
                cfsetispeed(&opt, B1200);
                return;
            }
            case IEC870_BAUNDRATE_2400:
            {
                cfsetospeed(&opt, B2400);
                cfsetispeed(&opt, B2400);
                return;
            }
            case IEC870_BAUNDRATE_4800:
            {
                cfsetospeed(&opt, B4800);
                cfsetispeed(&opt, B4800);
                return;
            }
            case IEC870_BAUNDRATE_9600:
            {
                cfsetospeed(&opt, B9600);
                cfsetispeed(&opt, B9600);
                return;
            }
            case IEC870_BAUNDRATE_14400:
            {
                cfsetospeed(&opt, B9600);
                cfsetispeed(&opt, B9600);
                return;
            }
            case IEC870_BAUNDRATE_19200:
            {
                cfsetospeed(&opt, B19200);
                cfsetispeed(&opt, B19200);
                return;
            }
            case IEC870_BAUNDRATE_38400:
            {
                cfsetospeed(&opt, B38400);
                cfsetispeed(&opt, B38400);
                return;
            }
            case IEC870_BAUNDRATE_56000:
            {
                cfsetospeed(&opt, B57600);
                cfsetispeed(&opt, B57600);
                return;
            }
            case IEC870_BAUNDRATE_57600:
            {
                cfsetospeed(&opt, B57600);
                cfsetispeed(&opt, B57600);
                return;
            }
            case IEC870_BAUNDRATE_115200:
            {
                cfsetospeed(&opt, B115200);
                cfsetispeed(&opt, B115200);
                return;
            }
            case IEC870_BAUNDRATE_128000:
            {
                cfsetospeed(&opt, B115200);
                cfsetispeed(&opt, B115200);
                return;
            }
            case IEC870_BAUNDRATE_256000:
            {
                cfsetospeed(&opt, B2500000);
                cfsetispeed(&opt, B2500000);
                return;
            }
        }
        cfsetospeed(&opt, B9600);
        cfsetispeed(&opt, B9600);
    }

    void set_com_comoption(com_port_option_type& opt, size_t databit, const rsparity_type& prt, const rsstopbit_type& stpbt) {
        opt.c_cflag |= INPCK; // enable parity
        bool needextend = ((prt == IEC870_MARKPARITY) || (prt == IEC870_SPACEPARITY));
        opt.c_cflag &= ~CSIZE;
        switch (databit) {
            case 5:
            {
                opt.c_cflag |= (needextend ? CS6 : CS5);
                break;
            }
            case 6:
            {
                opt.c_cflag |= (needextend ? CS7 : CS6);
                break;
            }
            case 7:
            {
                opt.c_cflag |= (needextend ? CS8 : CS7);
                break;
            }
            default:
            {
                opt.c_cflag |= CS8;
            }
        }

        switch (prt) {
            case IEC870_NOPARITY:
            {
                opt.c_cflag &= ~PARENB;
                break;
            }
            case IEC870_ODDPARITY:
            {
                opt.c_cflag |= PARENB;
                opt.c_cflag |= PARODD;
                break;
            }
            case IEC870_EVENPARITY:
            {
                opt.c_cflag |= PARENB;
                opt.c_cflag &= ~PARODD;
                break;
            }
            case IEC870_MARKPARITY:
            {
                opt.c_cflag &= ~PARENB;
                break;
            }
            case IEC870_SPACEPARITY:
            {
                opt.c_cflag &= ~PARENB;
                break;
            }
            default:
            {
                opt.c_cflag &= ~PARENB;
            }
        }

        if (stpbt == IEC870_ONESTOPBIT) {
            opt.c_cflag &= ~CSTOPB;
        } else {
            opt.c_cflag |= CSTOPB;
        }
    }

    void set_com_cominill(com_port_option_type& opt) {
        opt.c_oflag &= ~OPOST;
        opt.c_iflag |= (CLOCAL | CREAD);
        opt.c_iflag &= ~(IXON | IXOFF | IXANY);
    }

    void set_com_flowcontrol(com_port_option_type& opt, bool vl) {
        if (!vl)
            opt.c_iflag &= ~(IXON | IXOFF | IXANY);
        else
            opt.c_iflag &= ~(IXON | IXOFF | IXANY);
    }

#endif         

    boost::system::error_code iec60870_com_option_setter::store(com_port_option_type& opt, boost::system::error_code & ec) const {
        set_com_baudrate(opt, option_.baundrate());
        rsparity_type tmprty = IEC870_EVENPARITY;
        set_com_comoption(opt, 8, tmprty, IEC870_ONESTOPBIT);
        return boost::system::error_code();
    }



}

