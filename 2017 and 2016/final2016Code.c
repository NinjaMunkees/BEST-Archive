#pragma config(Motor,  port2,           rightMotor,    tmotorVex393_MC29, openLoop, driveRight)
#pragma config(Motor,  port4,           rightArm,      tmotorVex269_MC29, openLoop, reversed)
#pragma config(Motor,  port6,           leftServo,     tmotorServoStandard, openLoop)
#pragma config(Motor,  port7,           leftMotor,     tmotorVex269_MC29, openLoop)
#pragma config(Motor,  port8,           leftArm,       tmotorVex269_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

bool moveSpeed = false;
//bool tankEnabled = false;
void Jerk()
{
	while(vexRT[Btn7U] == true)//while left-top directional button is pressed, the robot will jerk forwards and backwards
	{
		motor[leftMotor] = 127;
		motor[rightMotor] = 127;
		wait1Msec(150);
		motor[leftMotor] = -127;
		motor[rightMotor] = -127;
		wait1Msec(350);
	}
}
task arcadeDrive()
{
	while(true)
	{

		if(moveSpeed == false)
		{
			if(abs(vexRT[Ch3]) < 10 && abs(vexRT[Ch4]) < 10) //Dead zone when joystick at approximately zero
			{
				motor[leftMotor]  = 0;
				motor[rightMotor] = 0;
			}
			else //Arcade drive on left joystick and full speed with 127 barrier
			{
				float y = vexRT[Ch4];
				float x = vexRT[Ch3];
				float xPlusY = x + y;
				float xMinusY = x - y;
				if(xPlusY > 127)
				{
					xPlusY = 127;
				}
				else if(xPlusY < -127)
				{
					xPlusY = -127;
				}
				if(xMinusY > 127)
				{
					xMinusY = 127;
				}
				else if(xMinusY < -127)
				{
					xMinusY = -127;
				}
				motor[leftMotor]  = xPlusY;
				motor[rightMotor] = xMinusY;
			}
		}
		else if(moveSpeed == true)//Optional half-speed
		{
			motor[leftMotor]  = (vexRT[Ch3] + vexRT[Ch4])/2;
			motor[rightMotor] = (vexRT[Ch3] - vexRT[Ch4])/2;
		}
		if(vexRT[Btn5D] == true)
		{
			moveSpeed = true;
		}
		if(vexRT[Btn5U] == true)
		{
			moveSpeed = false;
		}
		Jerk();
		/*while(tankEnabled == true)//Optional tank drive
		{
			motor[leftMotor] = vexRT[Ch3];
			motor[rightMotor] = vexRT[Ch2];
			Jerk();
		}*/
	}
}
task Arm()
{
	while(true)
	{
		motor[leftArm] = vexRT[Ch2]^3/(127^3); //Right joystick controls arm in arcade mode
		motor[rightArm] = vexRT[Ch2]^3/(127^3);
		/*while(tankEnabled == true)//Left triggers control arm in tank drive
		{
			if(vexRT[Btn5D] == true)
			{
				motor[leftArm] = -127;
				motor[rightArm] = -127;
			}
			else if(vexRT[Btn5U] == true)
			{
				motor[leftArm] = 127;
				motor[rightArm] = 127;
			}
			else
			{
				motor[leftArm] = 0;
				motor[rightArm] = 0;
			}
		}*/
	}
}

task Servo ()
{
	while(true)
	{
		if(vexRT[Btn6D] == true)
		{
			motor[leftServo] = 45; //total of 65 degrees of rotation between the two positions
		}
		else if(vexRT[Btn6U] == true)
		{
			motor[leftServo] = -35;
		}
	}
}

/*task controlSwitch()//Task for control schematic change
{
	while(true)
	{
		if(vexRT[Btn8U] == true)//Right-top directional button changes to tank drive
		{
			tankEnabled = true;
		}
		else if(vexRT[Btn8R] == true)//Right-right directional button changes back to arcade drive
		{
			tankEnabled = false;
		}
	}
}*/

task main()
{
	motor[leftServo] = -35;
	startTask(arcadeDrive);
	startTask(Arm);
	startTask(Servo);
	//startTask(controlSwitch);
	while(true)
	{
		wait1Msec(1);
	}
}
