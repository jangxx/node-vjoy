import vJoyDevice from "./vjoy_device";

declare class vJoyContinuousPOV {
    constructor(parent: vJoyDevice, povId: number);

    get id(): number;
    get value(): number;

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
    set(value: number): boolean;
}

export = vJoyContinuousPOV;