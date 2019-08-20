const vjoy = require('./build/Release/vjoy');

console.log(vjoy);

for (let key in vjoy) {
	console.log(key, vjoy[key]())
}