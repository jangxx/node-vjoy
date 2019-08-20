const vjoy_native = require('../build/Release/vjoy');

class vJoyButton {
	constructor(parent, buttonId) {
		this._parent = parent;

		this._id = buttonId;
		this._pressed = false;
	}

	get id() {
		return this._id;
	}

	get value() {
		return this._pressed;
	}

	/**
	 * Reset the internal value of the button abstraction
	 */
	_reset() {
		this._pressed = false;
	}

	/**
	 * Set this button to be pressed or not pressed
	 * @param {Boolean} value 
	 * @returns {Boolean}
	 */
	set(value) {
		if (!this._parent.initialized) throw new Error("Device is not initialized");

		let result = vjoy_native.SetBtn(this._parent.id, this.id, value);

		if (result) {
			this._pressed = value;
		}

		return result;
	}
}

module.exports = vJoyButton;