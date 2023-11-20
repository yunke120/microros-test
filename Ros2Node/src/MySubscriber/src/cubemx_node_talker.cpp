

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int32.hpp"

using namespace std::chrono_literals;

class Talker : public rclcpp::Node{
public:
  Talker():Node("talker_node_cpp"), count(0)
  {
      RCLCPP_INFO(this->get_logger(), "发布节点创建！");

      publisher_ = this->create_publisher<std_msgs::msg::Int32>("chatter", 10);

      timer_ = this->create_wall_timer(1s, std::bind(&Talker::on_timer, this));
  }
private:
  void on_timer()
  {
    auto msg = std_msgs::msg::Int32();
    msg.data = count++;
    RCLCPP_INFO(this->get_logger(), "发布方发布的消息: %d", msg.data);
    publisher_->publish(msg);
  }

  rclcpp::Publisher<std_msgs::msg::Int32>::SharedPtr publisher_;
  rclcpp::TimerBase::SharedPtr timer_;
  size_t count;
};

int main(int argc, char ** argv)
{

  rclcpp::init(argc, argv);

  rclcpp::spin(std::make_shared<Talker>());

  rclcpp::shutdown();
  return 0;
}
