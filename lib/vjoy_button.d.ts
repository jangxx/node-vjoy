import vJoyDevice from "./vjoy_device";

declare class vJoyButton {
    constructor(parent: vJoyDevice, buttonId: number);

    get id(): number;
    get value(): boolean;

    /**
     * Set this button to be pressed or not pressed
     * @param {Boolean} value
     * @returns {Boolean}
     */
    set(value: boolean): boolean;
}

export = vJoyButton;