import vJoyDevice from "./vjoy_device";

declare class vJoyAxis {
    constructor(parent: vJoyDevice, axisId: string);

    get id(): string;
    get value(): number;

    /**
     * Set the value of the axis between 1 and 32769 (0x8000)
     * @param {Number} value
     * @returns {Boolean}
     */
    set(value: number): boolean;
}

export = vJoyAxis;