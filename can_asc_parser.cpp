#include <cstdlib>
#include <ctime>
#include <cstring>
#include <iostream> 
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <cmath>
#include <limits>

typedef std::numeric_limits<double> dbl;

class can_message {
private:
  int channel, length;
  std::string time, id, byte_0, byte_1, byte_2, byte_3, byte_4, byte_5, byte_6, byte_7;
public:
  can_message(const std::string s){
    can_parse(s);
  }

  void can_parse(const std::string line){
    std::stringstream contents(line);
    int item_num = 0;
    while(contents.good()){
      std::string temp;
      getline(contents, temp, ' ');
      if (!temp.empty()){
	switch (item_num){
	case 0:
	  time = std::string(temp);
	  break;
	case 1:
	  channel = std::stoi(temp);
	  break;
	case 2:
	  id = temp.substr(0,8);
	  break;
	case 5:
	  length = std::stoi(temp);
	  break;
	case 6:
	  byte_0 = std::string(temp);
	  break;
	case 7:
	  byte_1 = std::string(temp);
	  break;
	case 8:
	  byte_2 = std::string(temp);
	  break;
	case 9:
	  byte_3 = std::string(temp);
	  break;
	case 10:
	  byte_4 = std::string(temp);
	  break;
	case 11:
	  byte_5 = std::string(temp);
	  break;
	case 12:
	  byte_6 = std::string(temp);
	  break;
	case 13:
	  byte_7 = std::string(temp);
	  break;
	default:
	  break;
	}
	item_num++;    
      }
    }
  }

  void print_message(){
    std::cout << time << " " << channel << " " << id << " " << length << " " << byte_0 << " " << byte_1 << " " << byte_2 << " " << byte_3 << " " << byte_4 << " " << byte_5 << " " << byte_6 << " " << byte_7<< std::endl;  
  }

  std::string get_pgn(){
    return id.substr(2,4);
  }
  
  std::string get_b0(){
    return byte_0;
  }

  std::string get_b1(){
    return byte_1;
  }

  std::string get_b2(){
    return byte_2;
  }
  
  std::string get_b3(){
    return byte_3;
  }

  std::string get_b4(){
    return byte_4;
  }

  std::string get_b5(){
    return byte_5;
  }

  std::string get_b6(){
    return byte_6;
  }

  std::string get_b7(){
    return byte_7;
  }
  
 
};

class gps_lat_long{
private:
  double latitude, longitude;

public:
  gps_lat_long(can_message message){
    parse_data(message);
  }

  void parse_data(can_message c){
    int lat0, lat1, lat2, lat3, lat_offset;
    int long0, long1, long2, long3, long_offset;

    //long long int lat_raw, long_raw;

    double lat_scale = 1E-7; double long_scale = 1E-7;

    lat0 = std::stoi(c.get_b0(), nullptr, 16); lat1 = std::stoi(c.get_b1(), nullptr, 16); lat2 = std::stoi(c.get_b2(), nullptr, 16); lat3 = std::stoi(c.get_b3(), nullptr, 16);
    long0 = std::stoi(c.get_b4(), nullptr, 16); long1 = std::stoi(c.get_b5(), nullptr, 16); long2 = std::stoi(c.get_b6(), nullptr, 16); long3 = std::stoi(c.get_b7(), nullptr, 16);
    
    //std::cout << lat0 << " " << lat1  << " " << lat2 << " " << lat3 <<  std::endl;

    latitude = ((lat0 + (lat1 * pow(2,8)) + (lat2 * pow(2,16)) + (lat3 * pow(2,24))) * lat_scale ) -210;
    longitude = ((long0 + (long1 * pow(2,8)) + (long2 * pow(2,16)) + (long3 * pow(2,24))) * long_scale ) -210;

    //print_message();
  }

  double get_lat(){
    return latitude;
  }

  double get_long(){
    return longitude;
  }

  void print_message(){
    std::cout.precision(dbl::max_digits10);
    std::cout << "Latitude: " << std::fixed << latitude << " Longitude: " << std::fixed << longitude << std::endl;
  }
  
};

class harvest_pinball_sensor{
private:
  int wand_0l, wand_0r, wand_1l, wand_1r;

public:
  harvest_pinball_sensor(can_message message){
    parse_data(message);
  }

  void parse_data(can_message c){
    int w0, w1, w2, w3, w4, w5;
    //int w1_l, w1_r, w4_l, w4_r;

    w0 = std::stoi(c.get_b2(), nullptr, 16); w1 = std::stoi(c.get_b3(), nullptr, 16);
    w2 = std::stoi(c.get_b4(), nullptr, 16); w3 = std::stoi(c.get_b5(), nullptr, 16);
    w4 = std::stoi(c.get_b6(), nullptr, 16); w5 = std::stoi(c.get_b7(), nullptr, 16);

    wand_0l = w0 + ((w1 & 15) * pow(2,8));
    wand_0r = (w2 * pow(2,4)) + ((w1 & 240) >> 4);
    wand_1l = w3 + ((w4 & 15) * pow(2,8));
    wand_1r = (w5 * pow(2,4)) + ((w4 & 240) >> 4);
    //speed = (sp0 + (sp1 * pow(2,8))) * kmh_scale * k_to_mi; 
    //direction = (dir0 + (dir1 * pow(2,8))) * deg_scale;
    //pitch = ((p0 + (p1 * pow(2,8))) * deg_scale) - 200;
    //altitude = ((alt0 + (alt1 * pow(2,8))) * m_scale) - 2500;

    //print_message();
  }

  double get_wand_0l(){
    return wand_0l;
  }

  double get_wand_0r(){
    return wand_0r;
  }

  double get_wand_1l(){
    return wand_1l;
  }

  double get_wand_1r(){
    return wand_1r;
  }

  double get_wand_0_sum(){
    return (wand_0l + wand_0r);
  }

  double get_wand_1_sum(){
    return (wand_1l + wand_1r);
  }

  void print_message(){
    std::cout.precision(dbl::max_digits10);
    std::cout << "Wand-0: " << get_wand_0_sum() << " Wand-1: " << get_wand_1_sum() << std::endl;
  }
  
};

class gps_speed_dir{
private:
  double speed, direction, pitch, altitude;

public:
  gps_speed_dir(can_message message){
    parse_data(message);
  }

  void parse_data(can_message c){
    int sp0, sp1, dir0, dir1;
    int p0, p1, alt0, alt1;

    double deg_scale = 0.0078125;
    double kmh_scale = 0.00390625;
    double m_scale = .125;
    double k_to_mi = 0.621371;

    dir0 = std::stoi(c.get_b0(), nullptr, 16); dir1 = std::stoi(c.get_b1(), nullptr, 16);
    sp0 = std::stoi(c.get_b2(), nullptr, 16); sp1 = std::stoi(c.get_b3(), nullptr, 16);
    p0 = std::stoi(c.get_b4(), nullptr, 16); p1 = std::stoi(c.get_b5(), nullptr, 16);
    alt0 = std::stoi(c.get_b6(), nullptr, 16); alt1 = std::stoi(c.get_b7(), nullptr, 16);

    speed = (sp0 + (sp1 * pow(2,8))) * kmh_scale * k_to_mi; 
    direction = (dir0 + (dir1 * pow(2,8))) * deg_scale;
    pitch = ((p0 + (p1 * pow(2,8))) * deg_scale) - 200;
    altitude = ((alt0 + (alt1 * pow(2,8))) * m_scale) - 2500;

    //print_message();
  }

  double get_speed(){
    return speed;
  }

  double get_dir(){
    return direction;
  }

  double get_pitch(){
    return pitch;
  }

  double get_altitude(){
    return altitude;
  }

  void print_message(){
    std::cout.precision(dbl::max_digits10);
    std::cout << "Speed: " << std::fixed << speed << " Direction: " << std::fixed << direction << std::endl;
  }
  
};
  

int main(int argc, char *argv[]){
  std::ifstream i;
  std::string line;
  std::vector<can_message*> mess;
  std::vector<gps_lat_long*> gll;
  std::vector<gps_speed_dir*> gsd;
  std::vector<harvest_pinball_sensor*> p12;
  std::vector<harvest_pinball_sensor*> p34;
  std::vector<harvest_pinball_sensor*> p56;
  std::vector<harvest_pinball_sensor*> p78;
  
  //can_message c;

  int line_count = 0;

  std::string path_gen = "/home/student/Desktop/ComS327/project2";
  
  i.open(path_gen + "/Collection 1 2022-10-29 15-12-42-279297 Partition 0.asc");   

  if (i.is_open()){
    std::cout << "Success" << std::endl;
  }

  if (i.is_open()){
    while(std::getline(i,line)){
      line_count++;      
      if ((line_count > 3) && (line_count <= 1300000000)){
      	//can_parse(line);
      	//can_message c = can_message(line);
      	//std::cout << line << std::endl;
	mess.push_back(new can_message(line));
      }
    }
  }

  for (int x = 0; x < (int) mess.size(); x++){
    //mess[x]->print_message();
    //int lat_long_pgn = 65267;
    std::string lat_long_pgn = "FEF3";
    std::string speed_dir_pgn = "FEE8";
    std::string pinball_sensor_pgn = "FF13";
    std::string row_12 = "01";
    std::string row_34 = "23";
    std::string row_56 = "45";
    std::string row_78 = "67";
    if (!(mess[x]->get_pgn().compare(lat_long_pgn))){
      gll.push_back(new gps_lat_long(*mess[x]));
    }
    if (!(mess[x]->get_pgn().compare(speed_dir_pgn))){
      gsd.push_back(new gps_speed_dir(*mess[x]));
    }
    if (!(mess[x]->get_pgn().compare(pinball_sensor_pgn))){
      if (!(mess[x]->get_b1().compare(row_12))){
	p12.push_back(new harvest_pinball_sensor(*mess[x]));
      }
      if (!(mess[x]->get_b1().compare(row_34))){
	p34.push_back(new harvest_pinball_sensor(*mess[x]));
      }
      if (!(mess[x]->get_b1().compare(row_56))){
	p56.push_back(new harvest_pinball_sensor(*mess[x]));
      }
      if (!(mess[x]->get_b1().compare(row_78))){
	p78.push_back(new harvest_pinball_sensor(*mess[x]));
      }
    }
    
  }

  for (int x = 0; x < (int) p56.size(); x++){
    p56[x]->print_message();
  }

  //std::string t_1 = "4A";
  //std::cout << std::stoi(t_1, nullptr, 16) << " -> " << t_1 << std::endl;
  //std::cout << mess[54]->get_pgn() << std::endl; //line 58
  //std::cout << mess[54]->get_b0() << std::endl;
  //std::cout << mess[54]->get_b1() << std::endl;
  //std::cout << mess[54]->get_b2() << std::endl;
  //std::cout << mess[54]->get_b3() << std::endl;
  //std::cout << mess[54]->get_b4() << std::endl;
  //std::cout << mess[54]->get_b5() << std::endl;
  //std::cout << mess[54]->get_b6() << std::endl;
  //std::cout << mess[54]->get_b7() << std::endl;

  //gps_lat_long g = gps_lat_long(*mess[54]);

  //std::cout << "Latitude: " << g.get_lat() << " Longitude: " << g.get_long() << " Size: " << (int) gll.size() <<std::endl;

  std::cout << (int) p12.size() << std::endl;
  std::cout << (int) p34.size() << std::endl;
  std::cout << (int) p56.size() << std::endl;
  std::cout << (int) p78.size() << std::endl;

  gll.clear();
  gsd.clear();
  p12.clear();
  p34.clear();
  p56.clear();
  p78.clear();
  
}
