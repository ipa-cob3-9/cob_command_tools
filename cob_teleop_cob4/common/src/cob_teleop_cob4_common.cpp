// ROS message includes
#include "ros/ros.h"
#include <sensor_msgs/JoyFeedback.h>
#include <geometry_msgs/Twist.h>
#include <brics_actuator/CartesianTwist.h>
#include <brics_actuator/CartesianTwist.h>
#include <brics_actuator/JointVelocities.h>
#include <brics_actuator/JointVelocities.h>
#include <geometry_msgs/Twist.h>
#include <brics_actuator/JointVelocities.h>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/Joy.h>

/* protected region user include files on begin */
#include <actionlib/client/simple_action_client.h>
#include <cob_script_server/ScriptAction.h>
/* protected region user include files end */

class cob_teleop_cob4_config
{
public:
    int button_deadman;
    double base_max_linear;
    double base_max_angular;
    double torso_max_angular;
    double head_max_angular;
    double sensor_ring_max_angular;
    double arm_joint_velocity_max;
    double arm_cartesian_max_linear;
    double arm_cartesian_max_angular;
    double gripper_max_velocity;
    int base_x;
    int base_y;
    int base_yaw;
    int arm_x;
    int arm_y;
    int arm_yaw;
    int arm_pitch_up;
    int arm_pitch_down;
    int arm_roll_right_and_ellbow;
    int arm_roll_left_and_ellbow;
    int arm_z_up;
    int arm_z_down;
    int gripper_open;
    int gripper_close;
    int arm_joint_up;
    int arm_joint_down;
    int arm_joint_left;
    int arm_joint_right;
    int arm_joint_12;
    int arm_joint_34;
    int arm_joint_56;
    int arm_joint_7_gripper;
    int axis_runfactor;
    int button_safety_override;
    int button_init_recover;
    int button_mode_switch;
    int torso_roll;
    int torso_pitch;
    int torso_yaw_left;
    int torso_yaw_right;
    int sensorring_yaw_left;
    int sensorring_yaw_right;
    int head_roll;
    int head_pitch;
    int head_yaw_left;
    int head_yaw_right;
};

class cob_teleop_cob4_data
{
// autogenerated: don't touch this class
public:
    //input data
    sensor_msgs::Joy in_joy;
    //output data
    sensor_msgs::JoyFeedback out_joy_feedback;
    bool out_joy_feedback_active;
    geometry_msgs::Twist out_base_controller_command;
    bool out_base_controller_command_active;
    brics_actuator::CartesianTwist out_arm_cart_left;
    bool out_arm_cart_left_active;
    brics_actuator::CartesianTwist out_arm_cart_right;
    bool out_arm_cart_right_active;
    brics_actuator::JointVelocities out_arm_joint_right;
    bool out_arm_joint_right_active;
    brics_actuator::JointVelocities out_arm_joint_left;
    bool out_arm_joint_left_active;
    geometry_msgs::Twist out_head_controller_command;
    bool out_head_controller_command_active;
    brics_actuator::JointVelocities out_sensorring_controller_command;
    bool out_sensorring_controller_command_active;
    geometry_msgs::Twist out_torso_controller_command;
    bool out_torso_controller_command_active;
};

class cob_teleop_cob4_impl
{
    /* protected region user member variables on begin */
    typedef actionlib::SimpleActionClient<cob_script_server::ScriptAction> Client;
    bool once;

    int mode;
    float run;
    float updown;
    float leftright;
    brics_actuator::JointVelocities sring;
    geometry_msgs::Twist head;
    geometry_msgs::Twist base;
    geometry_msgs::Twist torso;
    sensor_msgs::Joy joy;
    brics_actuator::JointVelocities left;
    brics_actuator::JointVelocities right;
    brics_actuator::JointValue jvalue;
       
    cob_script_server::ScriptGoal sss;
    /* protected region user member variables end */

public:
    cob_teleop_cob4_impl()
    {
        /* protected region user constructor on begin */
      Client client("script_server", true);
      ROS_INFO("Connecting to script_server");
      client.waitForServer();
      ROS_INFO("Connected");
       
        /* protected region user constructor end */
    }

    void configure(cob_teleop_cob4_config config)
    {
        /* protected region user configure on begin */ 

      mode=0;
      jvalue.unit="rad/sec";
      left.velocities.resize(7);
      right.velocities.resize(7);
      int i;
      for (i=0; i<7; i++)
      {
      //jvalue.joint_uri=("arm_left_%d_joint",(i+1)); //produces Ascii crap like:  
      left.velocities.at(i)=jvalue;
      //jvalue.joint_uri=("arm_right_%d_joint",(i+1));
      right.velocities.at(i)=jvalue;
      }
      left.velocities[0].joint_uri="arm_left_1_joint";
      left.velocities[1].joint_uri="arm_left_2_joint";
      left.velocities[2].joint_uri="arm_left_3_joint";
      left.velocities[3].joint_uri="arm_left_4_joint";
      left.velocities[4].joint_uri="arm_left_5_joint";
      left.velocities[5].joint_uri="arm_left_6_joint";
      left.velocities[6].joint_uri="arm_left_7_joint";
      right.velocities[0].joint_uri="arm_right_1_joint";
      right.velocities[1].joint_uri="arm_right_2_joint";
      right.velocities[2].joint_uri="arm_right_3_joint";
      right.velocities[3].joint_uri="arm_right_4_joint";
      right.velocities[4].joint_uri="arm_right_5_joint";
      right.velocities[5].joint_uri="arm_right_6_joint";
      right.velocities[6].joint_uri="arm_right_7_joint";
      sring.velocities.resize(1);
      sring.velocities[0].joint_uri="sensorring_joint";
      sring.velocities[0].unit="rad/sec";
      
        /* protected region user configure end */
    }

    void update(cob_teleop_cob4_data &data, cob_teleop_cob4_config config)
    {
        /* protected region user update on begin */
        
    data.out_base_controller_command_active=0; //on begin because default is 1
    data.out_sensorring_controller_command_active=0;
    data.out_torso_controller_command_active=0;
    data.out_arm_joint_left_active=0;
    data.out_arm_joint_right_active=0;
    data.out_head_controller_command_active=0;
    data.out_arm_cart_left_active=0;
    data.out_arm_cart_right_active=0;
    
    if (data.in_joy.buttons.size()!=17)//wait for complete joypad!
    {  
      ROS_WARN("joypad inactive! waiting for array of buttons. Move the Controller");
      return;
    }
    
    joy=data.in_joy;//bit smaller
    run=1-joy.axes[config.axis_runfactor];
    updown=(joy.buttons[config.arm_joint_up]-joy.buttons[config.arm_joint_down]);
    leftright=(joy.buttons[config.arm_joint_left]-joy.buttons[config.arm_joint_right]);
  
    if (joy.buttons[config.button_mode_switch] && not joy.buttons[config.button_deadman])//switch mode. gets executed multiple times
    {
      ++mode;
      if (mode >= 7)
      {
        mode = 0;
      }
      ROS_INFO("Mode switched to: %d",mode);
      ros::Duration(0.2).sleep();//wait (bad place)
      return;
    }
    if (joy.buttons[config.button_deadman])
    {
  
      switch (mode)
      {
      case 0: //Base
      base.linear.x=joy.axes[config.base_x]*config.base_max_linear*run;
      base.linear.y=joy.axes[config.base_y]*config.base_max_linear*run;
      base.angular.z=joy.axes[config.base_yaw]*config.base_max_angular*run;
      data.out_base_controller_command=base;
      data.out_base_controller_command_active=1;
      break;
      
      case 1: //arm cartesian left
      data.out_arm_cart_left.translation.x=(joy.axes[config.arm_x])*config.arm_cartesian_max_linear*run;
      data.out_arm_cart_left.translation.y=(joy.axes[config.arm_y])*config.arm_cartesian_max_linear*run;
      data.out_arm_cart_left.rotation.z=(joy.axes[config.arm_yaw])*config.arm_cartesian_max_angular*run;
      data.out_arm_cart_left.translation.z=(joy.buttons[config.arm_z_up]-joy.buttons[config.arm_z_down])*run*config.arm_cartesian_max_linear;
      data.out_arm_cart_left.rotation.x=(joy.buttons[config.arm_roll_left_and_ellbow]-joy.buttons[config.arm_roll_right_and_ellbow])*run*config.arm_cartesian_max_angular;
      data.out_arm_cart_left.rotation.y=(joy.buttons[config.arm_pitch_up]-joy.buttons[config.arm_pitch_down])*run*config.arm_cartesian_max_angular;
      data.out_arm_cart_left_active=1;
      break; //maybe these blocks should be smaller
      
      case 2: //arm_cartesian right
      data.out_arm_cart_right.translation.x=(joy.axes[config.arm_x])*config.arm_cartesian_max_linear*run;
      data.out_arm_cart_right.translation.y=(joy.axes[config.arm_y])*config.arm_cartesian_max_linear*run;
      data.out_arm_cart_right.rotation.z=(joy.axes[config.arm_yaw])*config.arm_cartesian_max_angular*run;
      data.out_arm_cart_right.translation.z=(joy.buttons[config.arm_z_up]-joy.buttons[config.arm_z_down])*run*config.arm_cartesian_max_linear;
      data.out_arm_cart_right.rotation.x=(joy.buttons[config.arm_roll_left_and_ellbow]-joy.buttons[config.arm_roll_right_and_ellbow])*run*config.arm_cartesian_max_angular;
      data.out_arm_cart_right.rotation.y=(joy.buttons[config.arm_pitch_up]-joy.buttons[config.arm_pitch_down])*run*config.arm_cartesian_max_angular;
      data.out_arm_cart_right_active=1;
      break;
      
      case 3: //arm_joints_left
      left.velocities[0].value=updown*joy.buttons[config.arm_joint_12]*run*config.arm_joint_velocity_max;
      left.velocities[1].value=leftright*joy.buttons[config.arm_joint_12]*run*config.arm_joint_velocity_max;
      left.velocities[2].value=updown*joy.buttons[config.arm_joint_34]*run*config.arm_joint_velocity_max;
      left.velocities[3].value=leftright*joy.buttons[config.arm_joint_34]*run*config.arm_joint_velocity_max;
      left.velocities[4].value=updown*joy.buttons[config.arm_joint_56]*run*config.arm_joint_velocity_max;
      left.velocities[5].value=leftright*joy.buttons[config.arm_joint_56]*run*config.arm_joint_velocity_max;
      left.velocities[6].value=updown*joy.buttons[config.arm_joint_7_gripper]*run*config.arm_joint_velocity_max;
      //left.joint_gripper=leftright*joy.buttons[config.arm_joint_7_gripper]*run*config.arm_joint_velocity_max;
      //left.velocities[0].timeStamp=ros::Time::now();
      data.out_arm_joint_left=left;
      data.out_arm_joint_left_active=1;
      break;
      
      case 4: //arm_joints_right
      right.velocities[0].value=updown*joy.buttons[config.arm_joint_12]*run*config.arm_joint_velocity_max;
      right.velocities[1].value=leftright*joy.buttons[config.arm_joint_12]*run*config.arm_joint_velocity_max;
      right.velocities[2].value=updown*joy.buttons[config.arm_joint_34]*run*config.arm_joint_velocity_max;
      right.velocities[3].value=leftright*joy.buttons[config.arm_joint_34]*run*config.arm_joint_velocity_max;
      right.velocities[4].value=updown*joy.buttons[config.arm_joint_56]*run*config.arm_joint_velocity_max;
      right.velocities[5].value=leftright*joy.buttons[config.arm_joint_56]*run*config.arm_joint_velocity_max;
      right.velocities[6].value=updown*joy.buttons[config.arm_joint_7_gripper]*run*config.arm_joint_velocity_max;
      //right.joint_gripper=rightright*joy.buttons[config.arm_joint_7_gripper]*run*config.arm_joint_velocity_max;
      //right.velocities[0].timeStamp=ros::Time::now();
      if (!joy.buttons[config.button_init_recover]){once=false;}
      if (joy.buttons[config.button_init_recover] && !once)
      {
      	init_recover("arm_right");
      	once=true;
      }
      data.out_arm_joint_right=right;
      data.out_arm_joint_right_active=1;
      break;
      
      case 5 : //automoves script      
      if (joy.buttons[4]){sss.component_name="head";}
      else if (joy.buttons[7]){sss.component_name="arm_left";}
      else if (joy.buttons[5]){sss.component_name="arm_right";}
      else if (joy.buttons[6]){sss.component_name="torso";}      
      else if (joy.buttons[12]){sss.component_name="sensorring";}
      else if (joy.buttons[15]){sss.component_name="gripper_left";}
      else if (joy.buttons[13]){sss.component_name="gripper_right";}
      else if (joy.buttons[14]){sss.component_name="base";}
      else {once=false; break;}
      if (!once)
      {
      	once=true;
      	ROS_INFO("Homing %s",sss.component_name.c_str());
      	sss.function_name="move";
      	sss.parameter_name="home";
      	//client.sendGoal(sss);
      }
      break;
      
      
      case 6: //case 6: sensorring head torso 
      //sensorring (Joints)
      sring.velocities[0].value=(joy.buttons[config.sensorring_yaw_left]-joy.buttons[config.sensorring_yaw_right])*config.sensor_ring_max_angular*run;
      data.out_sensorring_controller_command=sring;
      data.out_sensorring_controller_command_active=1;
      //head (Twist)
      head.angular.x=joy.axes[config.head_roll]*config.torso_max_angular*run;
      head.angular.y=joy.axes[config.head_pitch]*config.torso_max_angular*run;
      head.angular.z=(joy.buttons[config.head_yaw_left]-joy.buttons[config.head_yaw_right])*config.torso_max_angular*run;
      data.out_head_controller_command=head;
      data.out_head_controller_command_active=1;
      //torso (Twist)
      torso.angular.x=joy.axes[config.torso_roll]*config.torso_max_angular*run;
      torso.angular.y=joy.axes[config.torso_pitch]*config.torso_max_angular*run;
      torso.angular.z=(joy.buttons[config.torso_yaw_left]-joy.buttons[config.torso_yaw_right])*config.torso_max_angular*run;
      data.out_torso_controller_command=torso;
      data.out_torso_controller_command_active=1;
      break;
      }
  }
        /* protected region user update end */
    }


    /* protected region user additional functions on begin */
    void init_recover(std::string component)
  	{
  	sss.component_name=(component);
  	sss.function_name=("init");  	
  	//client.sendGoal(sss);
  	ROS_INFO("initialising %s",component.c_str());
  	sss.function_name=("recover");
  	ROS_INFO("recovering %s",component.c_str());
  	//client.sendGoal(sss);
  	}

    /* protected region user additional functions end */
};
