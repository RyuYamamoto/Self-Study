
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <boost/math/constants/constants.hpp>
#include <boost/asio.hpp>

class PoseEstimator
{
private:
	boost::asio::io_service io;
	boost::asio::serial_port serial_port;
public:
	std::vector<float> euler;
	std::vector<float> quaternion;

	PoseEstimator();
	~PoseEstimator();
	boost::system::error_code port_open(const std::string portname){
		boost::system::error_code err;
		serial_port.open(portname,err);
		if(!err){
			serial_port.set_option(boost::asio::serial_port_base::flow_control(boost::asio::serial_port_base::flow_control::none));
			serial_port.set_option(boost::asio::serial_port_base::stop_bits(boost::asio::serial_port_base::stop_bits::one));
		}
	}
	void set_baudrate(int baudrate){
		serial_port.set_option(boost::asio::serial_port_base::baud_rate(baudrate));
	}
	void set_parity(){
		serial_port.set_option(boost::asio::serial_port_base::parity::none);
	}
};