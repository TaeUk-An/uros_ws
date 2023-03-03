#include "lrc/lrc.hpp"

using namespace std::chrono_literals;

namespace LocalResiliencyCoordinator{

LRC::LRC(void) : Node("LRC")
{
  OcrPublisher_ = this->create_publisher<cpp_pubsub::msg::Lrc2ocr>("/lrc2ocr_msg", 10);  
  OcrSubscriber_ = this->create_subscription<cpp_pubsub::msg::Ocr2lrc>(    
    "/ocr2lrc_msg", 10, std::bind(&LRC::OcrCallback, this, std::placeholders::_1));
  OcrPublishTimer_ = this->create_wall_timer(500ms, std::bind(&LRC::Lrc2ocrCallback, this));
}

void LRC::Lrc2ocrCallback(void)
{
  auto msg = cpp_pubsub::msg::Lrc2ocr();
  msg.tar_vel = 1.0;                                                     
  msg.tar_dist = 0.8;                                                    
  msg.cur_dist = 0.62;                                                   
  msg.steer_angle = 5.0;                                                   
  msg.est_vel = 1.0;                                                   
  RCLCPP_INFO(this->get_logger(), "Publishing: '%.3f'", msg.tar_vel);
  OcrPublisher_->publish(msg);
}

void LRC::OcrCallback(const cpp_pubsub::msg::Ocr2lrc::SharedPtr msg)   
{
  RCLCPP_INFO(this->get_logger(), "I heard: '%.3f'", msg->ref_vel);     
  RCLCPP_INFO(this->get_logger(), "I heard: '%.3f'", msg->cur_vel);     
}

}
