#include <moveit/kinematics_base/kinematics_base.h>
#include <pluginlib/class_loader.h>
#include <ros/ros.h>
#include <geometry_msgs/Pose.h>
#include <gtest/gtest.h>


const std::string PLUGIN = "five_dof_arm_kinematics_moveit::KinematicsPlugin";
typedef boost::shared_ptr<kinematics::KinematicsBase> KinematicsBasePtr;


TEST(five_dof_arm_kinematics_moveit, wrong_arguments_fail_init)
{
    pluginlib::ClassLoader<kinematics::KinematicsBase> loader(
            "moveit_core", "kinematics::KinematicsBase");
    KinematicsBasePtr kinematics = loader.createInstance(PLUGIN);

    EXPECT_FALSE(kinematics->initialize("", "", "", "", 0.0));
}


TEST(five_dof_arm_kinematics_moveit, init_sets_values)
{
    pluginlib::ClassLoader<kinematics::KinematicsBase> loader(
            "moveit_core", "kinematics::KinematicsBase");
    KinematicsBasePtr kinematics = loader.createInstance(PLUGIN);

    EXPECT_TRUE(kinematics->initialize("/robot_description", "five_dof_arm",
            "base_link", "link5", 0.0));

    EXPECT_EQ("five_dof_arm", kinematics->getGroupName());
    EXPECT_EQ("base_link", kinematics->getBaseFrame());
    EXPECT_EQ("link5", kinematics->getTipFrame());
    EXPECT_NEAR(0.0, kinematics->getSearchDiscretization(), 0.001);
}


TEST(five_dof_arm_kinematics_moveit, wrong_kinematics_fails_init)
{
    pluginlib::ClassLoader<kinematics::KinematicsBase> loader(
            "moveit_core", "kinematics::KinematicsBase");
    KinematicsBasePtr kinematics = loader.createInstance(PLUGIN);

    EXPECT_FALSE(kinematics->initialize("/robot_description", "", "base_link",
            "link5", 0.0));
}


TEST(five_dof_arm_kinematics_moveit, wrong_base_and_tip_frame_fails_init)
{
    pluginlib::ClassLoader<kinematics::KinematicsBase> loader(
            "moveit_core", "kinematics::KinematicsBase");
    KinematicsBasePtr kinematics = loader.createInstance(PLUGIN);

    EXPECT_FALSE(kinematics->initialize("/robot_description", "", "base_link",
            "link5", 0.0));
}


TEST(five_dof_arm_kinematics_moveit, joint_and_link_names_not_empty_after_init)
{
    pluginlib::ClassLoader<kinematics::KinematicsBase> loader(
            "moveit_core", "kinematics::KinematicsBase");
    KinematicsBasePtr kinematics = loader.createInstance(PLUGIN);

    EXPECT_TRUE(kinematics->getJointNames().empty());
    EXPECT_TRUE(kinematics->getLinkNames().empty());

    EXPECT_TRUE(kinematics->initialize("/robot_description", "five_dof_arm",
            "base_link", "link5", 0.0));

    EXPECT_EQ(5, kinematics->getJointNames().size());
    EXPECT_EQ(5, kinematics->getLinkNames().size());

    EXPECT_EQ("joint1", kinematics->getJointNames()[0]);
    EXPECT_EQ("joint2", kinematics->getJointNames()[1]);
    EXPECT_EQ("joint3", kinematics->getJointNames()[2]);
    EXPECT_EQ("joint4", kinematics->getJointNames()[3]);
    EXPECT_EQ("joint5", kinematics->getJointNames()[4]);

    EXPECT_EQ("link1", kinematics->getLinkNames()[0]);
    EXPECT_EQ("link2", kinematics->getLinkNames()[1]);
    EXPECT_EQ("link3", kinematics->getLinkNames()[2]);
    EXPECT_EQ("link4", kinematics->getLinkNames()[3]);
    EXPECT_EQ("link5", kinematics->getLinkNames()[4]);
}


TEST(five_dof_arm_kinematics_moveit, inverse_kinematics_fails_before_init)
{
    pluginlib::ClassLoader<kinematics::KinematicsBase> loader(
            "moveit_core", "kinematics::KinematicsBase");
    KinematicsBasePtr kinematics = loader.createInstance(PLUGIN);

    geometry_msgs::Pose pose;
    std::vector<double> seed;
    std::vector<double> solution;
    moveit_msgs::MoveItErrorCodes error_code;

    EXPECT_FALSE(kinematics->getPositionIK(pose, seed, solution, error_code));
}

/**
TEST(five_dof_arm_kinematics_moveit, find_solution_for_candle_configuration)
{
    pluginlib::ClassLoader<kinematics::KinematicsBase> loader(
            "moveit_core", "kinematics::KinematicsBase");
    KinematicsBasePtr kinematics = loader.createInstance(PLUGIN);
    kinematics->initialize("/robot_description", "five_dof_arm", "base_link",
            "link5", 0.0);

    geometry_msgs::Pose pose;
    std::vector<double> seed(5, 0.0);
    std::vector<double> solution;
    moveit_msgs::MoveItErrorCodes error_code;

    pose.position.x = 0.057;
    pose.position.y = 0.0;
    pose.position.z = 0.535;

    EXPECT_TRUE(kinematics->getPositionIK(pose, seed, solution, error_code));

    EXPECT_NEAR( 2.9496, solution[0], 0.001);
    EXPECT_NEAR( 1.1344, solution[1], 0.001);
    EXPECT_NEAR(-2.5482, solution[2], 0.001);
    EXPECT_NEAR( 1.7890, solution[3], 0.001);
    EXPECT_NEAR( 2.9234, solution[4], 0.001);
}


TEST(five_dof_arm_kinematics_moveit, get_position_ik_fails_on_wrong_seed)
{
    pluginlib::ClassLoader<kinematics::KinematicsBase> loader(
            "moveit_core", "kinematics::KinematicsBase");
    KinematicsBasePtr kinematics = loader.createInstance(PLUGIN);
    kinematics->initialize("/robot_description", "arm_1", "arm_link_0",
            "arm_link_5", 0.0);

    geometry_msgs::Pose pose;
    std::vector<double> seed;
    std::vector<double> solution;
    moveit_msgs::MoveItErrorCodes error_code;

    pose.position.x = 0.057;
    pose.position.y = 0.0;
    pose.position.z = 0.535;

    EXPECT_FALSE(kinematics->getPositionIK(pose, seed, solution, error_code));
}
**/

int main(int argc, char **argv)
{
    ros::init(argc, argv, "five_dof_arm_kinematics_moveit_test");

    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
