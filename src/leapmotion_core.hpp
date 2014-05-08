#ifndef __LEAPMOTION_CORE__
#define __LEAPMOTION_CORE__

#include <boost/scoped_ptr.hpp>
#include "..\LeapSDK\include\Leap.h"
#include "runtime.hpp"
#include "v8_main_loop.hpp"

#include "events.hpp"

namespace aspect { 

class LEAPMOTION_API leapmotion : public v8_core::event_emitter, public Leap::Listener
{
public:
	explicit leapmotion(v8::Arguments const& args);
	~leapmotion();

private:
	typedef std::vector<std::string> strings;
	typedef boost::shared_ptr<strings> shared_strings;
	
	Leap::Controller controller;

    virtual void onInit(const Leap::Controller&);
    virtual void onConnect(const Leap::Controller&);
    virtual void onDisconnect(const Leap::Controller&);
    virtual void onExit(const Leap::Controller&);
    virtual void onFrame(const Leap::Controller&);
    virtual void onFocusGained(const Leap::Controller&);
    virtual void onFocusLost(const Leap::Controller&);

	void emit_event(shared_strings names, shared_strings values);

	std::string get_state(Leap::Gesture::State state);
};

} // aspect


#endif // __LEAPMOTION_CORE__
