import vJoyDevice from "./vjoy_device";

declare class vJoyDiscretePOV {
    constructor(parent: vJoyDevice, povId: number);

    get id(): number;
    get value(): number;

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
    set(value: number): boolean;
}

export = vJoyDiscretePOV;