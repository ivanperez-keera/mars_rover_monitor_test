#include <functional>
#include <memory>

#include "rclcpp/rclcpp.hpp"

#include "std_msgs/msg/bool.hpp"
#include "std_msgs/msg/empty.hpp"
#include "std_msgs/msg/u_int8.hpp"
#include "std_msgs/msg/u_int16.hpp"
#include "std_msgs/msg/u_int32.hpp"
#include "std_msgs/msg/u_int64.hpp"
#include "std_msgs/msg/int8.hpp"
#include "std_msgs/msg/int16.hpp"
#include "std_msgs/msg/int32.hpp"
#include "std_msgs/msg/int64.hpp"
#include "std_msgs/msg/float32.hpp"
#include "std_msgs/msg/float64.hpp"
#include <cstdint>

#include "monitor.h"
#include "monitor.c"

using std::placeholders::_1;

Float64Array wheel_velocity_controller_commands;

class CopilotRV : public rclcpp::Node {
  public:
    CopilotRV() : Node("copilotrv") {
      wheel_velocity_controller_commands_subscription_ = this->create_subscription<Float64Array>(
        "/wheel_velocity_controller/commands", 10,
        std::bind(&CopilotRV::wheel_velocity_controller_commands_callback, this, _1));

      propTooFast_publisher_ = this->create_publisher<std_msgs::msg::Empty>(
        "copilot/propTooFast", 10);

    }

    // Report (publish) monitor violations.
    void propTooFast() {
      auto output = std_msgs::msg::Empty();
      propTooFast_publisher_->publish(output);
    }

    // Needed so we can report messages to the log.
    static CopilotRV& getInstance() {
      static CopilotRV instance;
      return instance;
    }

  private:
    void wheel_velocity_controller_commands_callback(const Float64Array::SharedPtr msg) const {
      wheel_velocity_controller_commands = msg->data;
      step();
    }

    rclcpp::Subscription<Float64Array>::SharedPtr wheel_velocity_controller_commands_subscription_;

    rclcpp::Publisher<std_msgs::msg::Empty>::SharedPtr propTooFast_publisher_;

};

// Pass monitor violations to the actual class, which has ways to
// communicate with other applications.
void propTooFast() {
  CopilotRV::getInstance().propTooFast();
}

int main(int argc, char* argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<CopilotRV>());
  rclcpp::shutdown();
  return 0;
}
