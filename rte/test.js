pragma("event-queue");

var leapmotion = require("leapmotion");

var core = leapmotion.Core();

core.on('gesture', function(info){
	console.log("Gesture: ", info);
})





