#include <functional>
#include <memory>

#include "rclcpp/rclcpp.hpp"

#include "std_msgs/msg/empty.hpp"

using std::placeholders::_1;

class CopilotLogger : public rclcpp::Node {
  public:
    CopilotLogger() : Node("copilotlogger") {
      propTooFast_subscription_ = this->create_subscription<std_msgs::msg::Empty>(
        "copilot/propTooFast", 10,
        std::bind(&CopilotLogger::propTooFast_callback, this, _1));

    }

  private:
    void propTooFast_callback(const std_msgs::msg::Empty::SharedPtr msg) const {
      RCLCPP_INFO(this->get_logger(), "Copilot monitor violation: propTooFast");
    }

    rclcpp::Subscription<std_msgs::msg::Empty>::SharedPtr propTooFast_subscription_;

};

int main(int argc, char* argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<CopilotLogger>());
  rclcpp::shutdown();
  return 0;
}
