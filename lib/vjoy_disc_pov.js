const vjoy_native = require('../build/Release/vjoy');

class vJoyDiscretePOV {
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
	 * Set the direction of the POV switch.
	 * 0 = Up
	 * 1 = Right
	 * 2 = Down
	 * 3 = Left
	 * -1 = Neutral
	 * @param {Number} value 
	 * @returns {Boolean}
	 */
	set(value) {
		if (!this._parent.initialized) throw new Error("Device is not initialized");

		if (![-1, 0, 1, 2, 3].includes(value)) {
			throw new Error("Invalid value");
		}

		let result = vjoy_native.SetDiscPov(this._parent.id, this.id, value);

		if (result) {
			this._value = value;
		}

		return result;
	}
}

module.exports = vJoyDiscretePOV;