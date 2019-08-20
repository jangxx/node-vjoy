const vjoy_native = require('../build/Release/vjoy');

class vJoyContinuousPOV {
	constructor(parent, povId) {
		this._parent = parent;

		this._id = povId;
		this._value = -1;
	}

	get id() {
		return this._id;
	}

	get value() {
		return this._value;
	}

	/**
	 * Reset the internal value of the POV abstraction
	 */
	_reset() {
		this._value = -1;
	}

	/**
	 * Set the direction of the POV switch. Value has to be between -1 and 35999 where
	 * -1 = Neutral
	 * 0 = Up
	 * 9000 = Right
	 * 18000 = Down
	 * 27000 = Left
	 * @param {Number} value 
	 * @returns {Boolean}
	 */
	set(value) {
		if (!this._parent.initialized) throw new Error("Device is not initialized");

		if (value < -1 || value > 35999) {
			throw new Error("Invalid value");
		}

		let result = vjoy_native.SetContPov(this._parent.id, this.id, value);

		if (result) {
			this._value = value;
		}

		return result;
	}
}

module.exports = vJoyContinuousPOV;