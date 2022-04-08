//============================================================================
// Name        : main.cpp
// Author      : Willi Penner
//
// Description : Contains the main function. It also contains test functions
//               to test the connection to the controller and the movement of
//       		 the servos.
//============================================================================

#include "SerialCom.hpp"
#include "Pololu.hpp"
#include "ServoMotor.hpp"
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char * argv[])
{
	try{
	        int posAng = 0;
		int motorID = 0;
	        if(argc == 3){
		  posAng = stoi(argv[2]);
	          if(posAng>90){
		    posAng = 90;
		  }else if(posAng < -90){
		    posAng = -90;
		  }

		  motorID = stoi(argv[1]);
	          if(motorID>3){
		    motorID = 3;
		  }else if(motorID < 0){
		    posAng = 0;
		  }
		}else{
		  cout << "USAGE: " << argv[0] << " <motorID>[0...3] " << " <posAngDeg>[-90...90] " << endl;
		  exit(0);
		}

	    
		const char* portName = "/dev/ttyACM0";  // Linux
		Pololu conn(portName, 9600);
		// Open connection to COM port.
		conn.openConnection();
		conn.getErrors();


		// Define the servos of the robot manipulator
		ServoMotor arm(motorID, 6000, 3000	, &conn);
		cout << "max. pos.: " << arm.getMaxPosInAbs() << endl;
		cout << "min. pos.: " << arm.getMinPosInAbs() << endl;
		cout << "get current pos.: "  << arm.getPositionInAbs() << endl;


		arm.setMinMaxDegree(-90,90);
		arm.setPositionInDeg(posAng);


		unsigned short pMin, pMid, pMax;
		arm.showPololuValues(pMin,pMid,pMax);
		cout << pMin	<< " " << pMid << " " << pMax << endl;


		conn.closeConnection();
	}catch(IException *e){
		cout << e->getMsg() << endl;
	}catch(string e){
		cout << "string Error: " << e << endl;
	}catch(...){
		cout << "unknown error\n";
	}

	return 0;
}
