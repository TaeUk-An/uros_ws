#include "lrc/lrc.hpp"

int main(int argc, char* argv[]){
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<LocalResiliencyCoordinator::LRC>());
    rclcpp::shutdown();
    return 0;
}

