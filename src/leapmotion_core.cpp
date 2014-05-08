#include "leapmotion.hpp"
#include "leapmotion_core.hpp"

#include <emmintrin.h>

using namespace Leap;

using namespace v8;

namespace aspect { 

template<class T>
std::string t_to_string(T i)
{
    std::stringstream ss;
    std::string s;
    ss << i;
    s = ss.str();

    return s;
}

void leapmotion::onInit(const Controller& controller) {
  //std::cout << "Initialized" << std::endl;
}

void leapmotion::onConnect(const Controller& controller) {
  //std::cout << "Connected" << std::endl;
  controller.enableGesture(Gesture::TYPE_CIRCLE);
  controller.enableGesture(Gesture::TYPE_KEY_TAP);
  controller.enableGesture(Gesture::TYPE_SCREEN_TAP);
  controller.enableGesture(Gesture::TYPE_SWIPE);
}

void leapmotion::onDisconnect(const Controller& controller) {
  //Note: not dispatched when running in a debugger.
  //std::cout << "Disconnected" << std::endl;
}

void leapmotion::onExit(const Controller& controller) {
  //std::cout << "Exited" << std::endl;
}

void leapmotion::onFrame(const Controller& controller) {
  // Get the most recent frame and report some basic information
  const Frame frame = controller.frame();

  /*
  if (!frame.hands().isEmpty()) {
    // Get the first hand
    const Hand hand = frame.hands()[0];

    // Check if the hand has any fingers
    const FingerList fingers = hand.fingers();
    if (!fingers.isEmpty()) {
      // Calculate the hand's average finger tip position
      Vector avgPos;
      for (int i = 0; i < fingers.count(); ++i) {
        avgPos += fingers[i].tipPosition();
      }
      avgPos /= (float)fingers.count();
      std::cout << "Hand has " << fingers.count()
                << " fingers, average finger tip position" << avgPos << std::endl;
    }


    // Get the hand's sphere radius and palm position
    std::cout << "Hand sphere radius: " << hand.sphereRadius()
              << " mm, palm position: " << hand.palmPosition() << std::endl;

    // Get the hand's normal vector and direction
    const Vector normal = hand.palmNormal();
    const Vector direction = hand.direction();

    // Calculate the hand's pitch, roll, and yaw angles
    std::cout << "Hand pitch: " << direction.pitch() * RAD_TO_DEG << " degrees, "
              << "roll: " << normal.roll() * RAD_TO_DEG << " degrees, "
              << "yaw: " << direction.yaw() * RAD_TO_DEG << " degrees" << std::endl;
			  
  }
  */
  
  // Get gestures
  const GestureList gestures = frame.gestures();
  for (int g = 0; g < gestures.count(); ++g) {
    Gesture gesture = gestures[g];

    switch (gesture.type()) {
      case Gesture::TYPE_CIRCLE:
      {
        CircleGesture circle = gesture;
        std::string clockwiseness;

        if (circle.pointable().direction().angleTo(circle.normal()) <= PI/4) {
          clockwiseness = "clockwise";
        } else {
          clockwiseness = "counterclockwise";
        }

        // Calculate angle swept since last frame
        float sweptAngle = 0;
        if (circle.state() != Gesture::STATE_START) {
          CircleGesture previousUpdate = CircleGesture(controller.frame(1).gesture(circle.id()));
          sweptAngle = (circle.progress() - previousUpdate.progress()) * 2 * PI;
        }

		shared_strings names = boost::make_shared<strings>(6);
		shared_strings values = boost::make_shared<strings>(6);

		int i = 0;
		(*names)[i] = "type"; (*values)[i] = "circle";i++;
		(*names)[i] = "id"; (*values)[i] = t_to_string(gesture.id());i++;
		(*names)[i] = "progress"; (*values)[i] = t_to_string(circle.progress());i++;
		(*names)[i] = "radius"; (*values)[i] = t_to_string(circle.radius());i++;
		(*names)[i] = "angle"; (*values)[i] = t_to_string(sweptAngle * RAD_TO_DEG);i++;
		(*names)[i] = "clockwiseness"; (*values)[i] = clockwiseness; i++;

		runtime::main_loop().schedule(boost::bind(&leapmotion::emit_event, this, names, values));

		/*
        std::cout << "Circle id: " << gesture.id()
                  << ", state: " << gesture.state()
                  << ", progress: " << circle.progress()
                  << ", radius: " << circle.radius()
                  << ", angle " << sweptAngle * RAD_TO_DEG
                  <<  ", " << clockwiseness << std::endl;
				  */
        break;
      }
      case Gesture::TYPE_SWIPE:
      {
        SwipeGesture swipe = gesture;
		
		shared_strings names = boost::make_shared<strings>(7);
		shared_strings values = boost::make_shared<strings>(7);

		int i = 0;
		(*names)[i] = "type"; (*values)[i] = "swipe";i++;
		(*names)[i] = "id"; (*values)[i] = t_to_string(gesture.id());i++;
		(*names)[i] = "state"; (*values)[i] = get_state(gesture.state());i++;
		(*names)[i] = "direction_x"; (*values)[i] = t_to_string(swipe.direction().x); i++;
		(*names)[i] = "direction_y"; (*values)[i] = t_to_string(swipe.direction().y); i++;
		(*names)[i] = "direction_z"; (*values)[i] = t_to_string(swipe.direction().z); i++;
		(*names)[i] = "speed"; (*values)[i] = t_to_string(swipe.speed()); i++;

		runtime::main_loop().schedule(boost::bind(&leapmotion::emit_event, this, names, values));

		/*
        std::cout << "Swipe id: " << gesture.id()
          << ", state: " << gesture.state()
          << ", direction: " << swipe.direction()
          << ", speed: " << swipe.speed() << std::endl;
		  */
        break;
      }
      case Gesture::TYPE_KEY_TAP:
      {
        KeyTapGesture tap = gesture;
		shared_strings names = boost::make_shared<strings>(8);
		shared_strings values = boost::make_shared<strings>(8);

		int i = 0;
		(*names)[i] = "type"; (*values)[i] = "key_tap";i++;
		(*names)[i] = "id"; (*values)[i] = t_to_string(gesture.id());i++;
		(*names)[i] = "direction_x"; (*values)[i] = t_to_string(tap.direction().x); i++;
		(*names)[i] = "direction_y"; (*values)[i] = t_to_string(tap.direction().y); i++;
		(*names)[i] = "direction_z"; (*values)[i] = t_to_string(tap.direction().z); i++;
		(*names)[i] = "position_x"; (*values)[i] = t_to_string(tap.position().x); i++;
		(*names)[i] = "position_y"; (*values)[i] = t_to_string(tap.position().y); i++;
		(*names)[i] = "position_z"; (*values)[i] = t_to_string(tap.position().z); i++;

		runtime::main_loop().schedule(boost::bind(&leapmotion::emit_event, this, names, values));

		/*
        std::cout << "Key Tap id: " << gesture.id()
          << ", state: " << gesture.state()
          << ", position: " << tap.position()
          << ", direction: " << tap.direction()<< std::endl;
		  */
        break;
      }
      case Gesture::TYPE_SCREEN_TAP:
      {
        ScreenTapGesture tap = gesture;
		shared_strings names = boost::make_shared<strings>(8);
		shared_strings values = boost::make_shared<strings>(8);

		int i = 0;
		(*names)[i] = "type"; (*values)[i] = "screen_tap";i++;
		(*names)[i] = "id"; (*values)[i] = t_to_string(gesture.id());i++;
		(*names)[i] = "direction_x"; (*values)[i] = t_to_string(tap.direction().x); i++;
		(*names)[i] = "direction_y"; (*values)[i] = t_to_string(tap.direction().y); i++;
		(*names)[i] = "direction_z"; (*values)[i] = t_to_string(tap.direction().z); i++;
		(*names)[i] = "position_x"; (*values)[i] = t_to_string(tap.position().x); i++;
		(*names)[i] = "position_y"; (*values)[i] = t_to_string(tap.position().y); i++;
		(*names)[i] = "position_z"; (*values)[i] = t_to_string(tap.position().z); i++;

		runtime::main_loop().schedule(boost::bind(&leapmotion::emit_event, this, names, values));

		/*
        std::cout << "Screen Tap id: " << gesture.id()
        << ", state: " << gesture.state()
        << ", position: " << screentap.position()
        << ", direction: " << screentap.direction()<< std::endl;
		*/
        break;
      }
      default:
        //std::cout << "Unknown gesture type." << std::endl;
        break;
    }
  }
}


void leapmotion::onFocusGained(const Controller& controller) {
  //std::cout << "Focus Gained" << std::endl;
}

void leapmotion::onFocusLost(const Controller& controller) {
  //std::cout << "Focus Lost" << std::endl;
}

std::string leapmotion::get_state(Gesture::State state)
{
	switch(state)
	{
		case Gesture::State::STATE_INVALID : return "invalid";
		case Gesture::State::STATE_START : return "start";
		case Gesture::State::STATE_STOP : return "stop";
		case Gesture::State::STATE_UPDATE : return "update";
	}
	return "";
}
	
leapmotion::leapmotion(v8::Arguments const& v8_args)
{
  // Have the sample listener receive events from the controller
  controller.addListener(*this);
}

leapmotion::~leapmotion()
{
  controller.removeListener(*this);
}

void leapmotion::emit_event(shared_strings names, shared_strings values)
{
	HandleScope scope;

	Handle<Object> object = Object::New();

	if((*names).size() == (*values).size())
	{
		for (int i = 0; i < (*names).size(); i++)
		{
			if(
				(*names)[i] == "speed" || 
				(*names)[i] == "progress" || 
				(*names)[i] == "radius" || 
				(*names)[i] == "angle" ||
				(*names)[i] == "direction_x" || 
				(*names)[i] == "direction_y" || 
				(*names)[i] == "direction_z" ||
				(*names)[i] == "position_x" ||
				(*names)[i] == "position_y" ||
				(*names)[i] == "position_z" 
				)
			{
				double v = (double)atof((*values)[i].c_str());
				set_option(object, (*names)[i].c_str(), v);

			} else if(
				(*names)[i] == "id" 
				)
			{
				int v = (int)atoi((*values)[i].c_str());
				set_option(object, (*names)[i].c_str(), v);
			} else
			{
				set_option(object, (*names)[i].c_str(), (*values)[i].c_str());
			}
		}
	}

	v8::Handle<v8::Value> args[1] = { object };
	emit("gesture", 1, args);
}


} // namespace aspect

