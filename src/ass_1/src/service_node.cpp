#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "nav_msgs/Odometry.h"
#include "ass_1/GetPosition.h"
#include <std_msgs/Int32.h>

#include <iostream>
#include <fstream>
#include <string>
#include <istream>

using namespace std;

int **Map;					// Matrix to storage the map
bool completed = false;		// Variable for kwnowing when the whole map has been visited

// Variables for knowing if I'm at the end of the map
bool endofmapD = false;
bool endofmapR = false;
bool endofmapU = false;
bool endofmapL = false;

size_t row, col;	// Dimension of the map/matrix
ros::Publisher pub_completed;


// Function that, knowing the actual odometry of the robot, decide which is the target position and which direction of the velocity the robot needs to get to the target
int *function_map(int a, int b)
  {
	int x = a;					// Actual x coordinate of the robot
 	int y = b;					// Actual y coordinate of the robot
 	int *target = new int[4];	// 0 = target_position_x, 1 = target_position_y, 2 = velocity_along_x, 3 = velocity_along_y
	target[2] = 0; 
	target[3] = 0;

	bool corner_1 = false;
	bool corner_2 = false;
	bool corner_3 = false;
	bool corner_4 = false;
	bool border_up = false;
	bool border_left = false;
	bool border_down = false;
	bool border_right = false;
	bool center = false;

	// Targets depending on the direction
	int *up = new int[4]; 
	up[0] = x-1;
	up[1] = y;
	up[2] = -1;
	up[3] = 0;
	int *down = new int[4];
	down[0] = x+1;
	down[1] = y;
	down[2] = 1;
	down[3] = 0;
	int *left = new int[4];
	left[0] = x;
	left[1] = y-1;
	left[2] = 0;
	left[3] = -1;
	int *right = new int[4];
	right[0] = x;
	right[1] = y+1;
	right[2] = 0;
	right[3] = 1;

	// Taking the robot inside the map if it is not already
	if (x < 0 || x > row-1 || y < 0 || y > col-1) {
		if (x < 0 && y >= 0 && y < col-1) {				// If the robot is above the up border
			cout << "The robot is above the up border\n";
			if (Map[0][y] != -1) {
				target[0] = 0;
				target[1] = y;
				target[2] = 1;
			}
			else {
				if (y == col-1 || endofmapD == true) {
					endofmapD = true;
					target = left;
				}
				else 
					target = right;
			}
		}
		else if (y < 0 && x >= 0 && x < row-1) {		// If the robot is on the left of the left border
			cout << "The robot is on the left of the left border\n";
			if (Map[x][0] != -1) {
				target[0] = x;
				target[1] = 0;
				target[3] = 1;
			}
			else {
				if (x == row-1 || endofmapL == true) {
					endofmapL = true;
					target = up;
				}
				else 
					target = down;
			}
		}
		else if (y >= col && x >= 0 && x < row-1) {		// If the robot is on the right of the right border
			cout << "The robot is on the right of the right border\n";
			if (Map[x][col-1] != -1) {
				target[0] = x;
				target[1] = col-1;
				target[3] = -1;
			}
			else {
				if (x == row-1 || endofmapR == true) {
					endofmapR = true;
					target = up;
				}
				else 
					target = down;
			}
		}
		else if (x >= row && y >= 0 && y < col-1) {		// If the robot is under the down border
			cout << "The robot is under the down border\n";
			if (Map[row-1][y]) {
				target[0] = row-1;
				target[1] = y;
				target[2] = -1;
			}
			else {
				if (y == col-1 || endofmapU == true){
					endofmapU = true;
					target = left;
				}
				else 
					target = right;
			}
		}

	}

	// If the robot is inside the map
	else {
		cout << "The robot is inside the map.\n";
		// Checking in which type of position is the robot
		if (x == 0) {
			if (y == 0) {
				corner_1 = true;		// Position [0,0] of the map
			}
			else if (y == (col-1)) {
				corner_2 = true;		// Position [0, col-1] of the map
			}
			else {
				border_up = true;		// All the positions that are in the first row of the matrix
			}
		}
		else if (x == (row-1)) {
			if (y == 0) {
				corner_4 = true;		// Position [row-1, 0] of the map
			}
			else if (y == (col-1)) {
				corner_3 = true;		// Position [row-1, col-1] of the map
			}
			else {
				border_down = true;		// All the positions that are in the last row of the matrix
			}
		}
		else {
			if (y == 0) {
				border_left = true;		// All the positions that are in the first column of the matrix
			}
			else if (y == (col-1)) {
				border_right = true;	// All the positions that are in the last column of the matrix
			}
			else {
				center = true;			// All the positions that are not corners or borders
			}
		}

		// If the robot is in the left-up corner
		if (corner_1) {
			// It can only go down or right
			int value_down = Map[x+1][y]; 
	 		int value_right = Map[x][y+1];
		
			if (value_down >= 0) {
				if (value_right >= 0) {
					if (value_down <= value_right) {
						target = down;
					}
					else {
						target = right;
					}
				}
			}
			else {
				target = right;
			}
		}	

		// If the robot is in the right-up corner
		if (corner_2) {
			// It can only go down or left
			int value_down = Map[x+1][y];
	 		int value_left = Map[x][y-1];
		
			if (value_left >= 0) {
				if (value_down >= 0) {
					if (value_left <= value_down) {
						target = left;
					}
					else {
						target = down;
					}
				}
			}
			else {
				target = down;
			}
		}

		// If the robot is in the right-down corner
		if (corner_3) {
			// It can only go up or left
			int value_up = Map[x-1][y];
	 		int value_left = Map[x][y-1];
		
			if (value_up >= 0) {
				if (value_left >= 0) {
					if (value_up <= value_left) {
						target = up;
					}
					else {
						target = left;
					}
				}
			}
			else {
				target = left;
			}
		}

		// If the robot is in the left-down corner
		if (corner_4) {
			// It can only go up or right
			int value_up = Map[x-1][y];
	 		int value_right = Map[x][y+1];
		
			if (value_right >= 0) {
				if (value_up >= 0) {
					if (value_right <= value_up) {
						target = right;
					}
					else {
					target = up;
					}
				}
			}
			else {
				target = up;
			}
		}

		// If the robot is in the left border
		if(border_left) {
			// It can not go left
		 	int value_up = Map[x-1][y];
		 	int value_down = Map[x+1][y];
		 	int value_right = Map[x][y+1];

			if (value_down >= 0) {
				if (value_down <= value_right || value_right == -1) {
					if (value_down <= value_up || value_up == -1) { 
						target = down;
					}				    
					else { 
						target = up;
					 }
				}
				else { 
					 if (value_right <= value_up || value_up == -1) {
						target = right;
					}
					else { 
						target = up;
					}
				}
			}	  
			else if ((value_right <= value_up || value_up == -1) && value_right != -1) {
				 		target = right;
			}
			else {
				 		target = up;
	  		}
		}

		// If the robot is in the up border
		if(border_up) {
			// It can not go up
	 		int value_left = Map[x][y-1];  
		 	int value_down = Map[x+1][y];  
		 	int value_right = Map[x][y+1]; 

			if (value_left >= 0) {
				if (value_left <= value_down || value_down == -1) {
					if (value_left <= value_right || value_right == -1) { 
						target = left;
					}				    
					else { 
				 		target = right;
					 }
				}
				else { 
					 if (value_down <= value_right || value_right == -1) { 
						target = down;
					}
					else { 
				 		target = right;
					}
				}
			}	  
			else if ((value_down <= value_right || value_right == -1) && value_down != -1) {
						target = down;
			}
			else { 
				 		target = right;
	  		}
		}

		// If the robot is in the right border
		if(border_right) {
			// It can not go right
		 	int value_up = Map[x-1][y];    
	 		int value_left = Map[x][y-1];  
		 	int value_down = Map[x+1][y];  

			if (value_up >= 0) {
				if (value_up <= value_left || value_left == -1) {
					if (value_up <= value_down || value_down == -1) { 
				 		target = up;
					}				    
					else { 
						target = down;
					 }
				}
				else { 
					 if (value_left <= value_down || value_down == -1) { 
						target = left;
					}
					else {
						target = down;
					}
				}
			}	  
			else if ((value_left <= value_down || value_down == -1) && value_left != -1) {
						target = left;
			}
			else { 
						target = down;
	  		}
		}

		// If the robot is in the down border
		if(border_down) {
			// It can not go down
		 	int value_right = Map[x][y+1]; 
		 	int value_up = Map[x-1][y];    
	 		int value_left = Map[x][y-1];  

			if (value_right >= 0) {
				if (value_right <= value_up || value_up == -1) {
					if (value_right <= value_left || value_left == -1) { 
				 		target = right;
					}				    
					else { 
						target = left;
					 }
				}
				else { 
					 if (value_up <= value_left || value_left == -1) { 
				 		target = up;
					}
					else { 
						target = left;
					}
				}
			}	  
			else if ((value_up <= value_left || value_left == -1) && value_up != -1) {
				 		target = up;
			}
			else { 
						target = left;
	  		}
		}
	
		// If the robot is in a center position
		if (center) {
			// It can go in all the directions
		 	int value_down = Map[x+1][y];  
			int value_right = Map[x][y+1];
		 	int value_up = Map[x-1][y];
	 		int value_left = Map[x][y-1]; 

			if ((value_down <= value_right || value_right == -1) && (value_down <= value_up || value_up == -1) && (value_down <= value_left || value_left ==-1) && value_down != -1) {
				target = down;
			}

			else if ((value_right <= value_down || value_down == -1) && (value_right <= value_up || value_up == -1) && (value_right <= value_left || value_left ==-1) && value_right != -1) {
				target = right;
			}

			else if ((value_up <= value_down || value_down == -1) && (value_up <= value_right || value_right == -1) && (value_up <= value_left || value_left ==-1) && value_up != -1) {
				target = up;
			}

			else {
				target = left;
			}
		}
	}

	// If the value of the target position is inside the map (so it's not an intermediate position used to take the robot inside the map)
	if (target[0] >= 0 && target[0] < row && target[1] >= 0 && target[1] < col)
		Map[target[0]][target[1]] ++;	// Updating the position of the map relative to the target

	// Printing the updated map
	cout << "Updated map:\n";
	for (size_t i = 0; i < row; ++i) {
        for (size_t j = 0; j < col; ++j){
		if(Map[i][j] != -1)
			cout<<" ";
        	std::cout <<  Map[i][j] << " ";
        }	
        std::cout << "\n";
    }
	std::cout << "------------------\n";

    
	int flag = 0; 
    for (int i=0; i<row; i++) {
		for (int j=0; j<col; j++) {
			if( Map[i][j] != 0)		// Counting how many elements of the map are different than zero
				flag ++;
		}
	}
	if (flag == row*col) {			// When all the elements are different than zero the game is completed, the robots have visited the whole map
		completed = true;

		// Comunicating to the controller_node that the game is completed
		std_msgs::Int32 msg;
		msg.data = 1;
		pub_completed.publish(msg);

		exit(0);
	}	

 	return target;
}
		

bool goal_position_function(ass_1::GetPosition::Request &req, ass_1::GetPosition::Response &res)
  {
	// Receiving the odometry from the client
	int my_x = round(req.my_position_x);
	int my_y = round(req.my_position_y);

	int *goal = new int [4];
	
	// Calling the function that choose the target position and the velocities direction
	goal = function_map(my_x, my_y);

	// Giving response to the client
	res.target_x = goal[0];		// Target position x
	res.target_y = goal[1];		// Targer position y
	res.vel_x = goal[2];		// Velocity along x
	res.vel_y = goal[3];		// Velocity along y
 	return true;
}


int main(int argc, char **argv)
 {	

	std::ifstream inFile("/home/experimental_ws/src/ass_1/map/map_1.txt");

	// Reading the number of column and rows of the matrix from the file.txt
    if(inFile) {
        inFile >> row >> col;
    }

	// Creating matrix for the map
    Map = new int*[row];
    for(size_t i = 0; i < row; ++i) {
        Map[i] = new int[col];
    }

	// Reading the matrix
    while(inFile) {
        std::string dummy;
        getline(inFile, dummy);
        for (size_t i = 0; i < row; ++i) {
            		for (size_t j = 0; j < col; ++j) {
                	inFile >> Map[i][j];
            	}
        }
    }

	// Printing the map
	cout<< "Initial map: \n";
	for (size_t i = 0; i < row; ++i) {
        for (size_t j = 0; j < col; ++j){
		if(Map[i][j] != -1)
			cout<<" ";
        	std::cout <<  Map[i][j] << " ";
        }	
        std::cout << "\n";
    }

	ros::init(argc, argv, "goal_position_server");
	ros::NodeHandle n;
	pub_completed = n.advertise<std_msgs::Int32>("/completed", 5);		// Publisher of the end of the algorithm
	ros::ServiceServer service = n.advertiseService("goal_position", goal_position_function);
	ros::spin();

	if (completed = true) {
		for (size_t i = 0; i < row; ++i ) {
		    delete [] Map[i];
		}
		delete [] Map;
	}
	return 0;
}
