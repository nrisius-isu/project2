#include <cstdlib>
#include <ctime>
#include <cstring>
#include <iostream> 
#include <sstream>
#include <string>
#include <vector>
#include <fstream>

class can_message {
private:
  //long double time;
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

    //print_message();
  }

  void print_message(){
    std::cout << time << " " << channel << " " << id << " " << length << " " << byte_0 << " " << byte_1 << " " << byte_2 << " " << byte_3 << " " << byte_4 << " " << byte_5 << " " << byte_6 << " " << byte_7<< std::endl;  
  }
  
 
};

class gps_lat_long{
public:
  float latitude, longitude;
};


// void can_parse(const std::string line){
//   std::stringstream contents(line);
//   int item_num = 0;
//   can_message c;
//   while(contents.good()){
//     std::string temp;
//     getline(contents, temp, ' ');
//     if (!temp.empty()){
//       //std::cout << temp.size() << ": ";
//       //std::cout << temp << std::endl;
//       //std::cout << temp << ' ';
//     switch (item_num){
//     case 0:
//       //c.time = std::stold(temp);
//       c.time = std::string(temp);
//       //std::cin >> c.time;
//       //std::stringstream(temp) >> c.time;
//       break;
//     case 1:
//       c.channel = std::stoi(temp);
//       break;
//     case 2:
//       c.id = temp.substr(0,8);
//       break;
//     case 5:
//       c.length = std::stoi(temp);
//     case 6:
//       c.byte_0 = std::string(temp);
//     case 7:
//       c.byte_1 = std::string(temp);
//     case 8:
//       c.byte_2 = std::string(temp);
//     case 9:
//       c.byte_3 = std::string(temp);
//     case 10:
//       c.byte_4 = std::string(temp);
//     case 11:
//       c.byte_5 = std::string(temp);
//     case 12:
//       c.byte_6 = std::string(temp);
//     case 13:
//       c.byte_7 = std::string(temp);
//     default:
//       break;
//     }
//     item_num++;
     
//     }
//   }

//   std::cout << c.time << " " << c.channel << " " << c.id << " " << c.length << " " << c.byte_0 << " " << c.byte_1 << " " << c.byte_2 << " " << c.byte_3 << " " << c.byte_4 << " " << c.byte_5 << " " << c.byte_6 << " " << c.byte_7<< std::endl;  

// }

int main(int argc, char *argv[]){
  std::ifstream i;
  std::string line;
  std::vector<can_message*> mess;
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

  for (int x; x < (int) mess.size(); x++){
    //mess[x]->can_message::print_message();
    mess[x]->print_message();
  }

  //std::string t_1 = "4A";
  //std::cout << std::stoi(t_1, nullptr, 16) << " -> " << t_1 << std::endl;
  
  
}
