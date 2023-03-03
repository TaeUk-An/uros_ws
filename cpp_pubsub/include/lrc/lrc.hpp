#pragma once
#include <chrono>
#include <functional>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int32.hpp"
#include "std_msgs/msg/string.hpp"

#include "cpp_pubsub/msg/lrc2ocr.hpp"
#include "cpp_pubsub/msg/ocr2lrc.hpp"

using namespace std::chrono_literals;

namespace LocalResiliencyCoordinator{

class LRC : public rclcpp::Node
{
public:
     LRC();

private:
    void Lrc2ocrCallback(void);
    void OcrCallback(const cpp_pubsub::msg::Ocr2lrc::SharedPtr msg);
    rclcpp::Subscription<cpp_pubsub::msg::Ocr2lrc>::SharedPtr OcrSubscriber_;
    rclcpp::Publisher<cpp_pubsub::msg::Lrc2ocr>::SharedPtr OcrPublisher_;
    rclcpp::TimerBase::SharedPtr OcrPublishTimer_;
};

}
