#include "leapmotion.hpp"
#include "library.hpp"

#include "leapmotion_core.hpp"

namespace aspect { 

using namespace v8;

DECLARE_LIBRARY_ENTRYPOINTS(leapmotion_install, leapmotion_uninstall);

Handle<Value> leapmotion_install()
{
	v8pp::module leapmotion_module;
	
	v8pp::class_<leapmotion> leapmotion_class(v8pp::v8_args_ctor);
	leapmotion_class
		.inherit<v8_core::event_emitter>()
		;

	leapmotion_module.set("Core", leapmotion_class);

	return leapmotion_module.new_instance();
}

void leapmotion_uninstall(Handle<Value> library)
{
	v8pp::class_<leapmotion>::destroy_objects();
}

} // ::aspect
