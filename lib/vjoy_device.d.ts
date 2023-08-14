import vJoyButton from "./vjoy_button";
import vJoyContinuousPOV from "./vjoy_cont_pov";
import vJoyDiscretePOV from "./vjoy_disc_pov";
import { AxisName } from "./vjoy";
import vJoyAxis from "./vjoy_axis";

declare class vJoyDevice {
    /**
     * Convenience method to create and initialize a new vJoyDevice
     * @param {Number} id
     * @return {vJoyDevice}
     */
    static create(id: number): vJoyDevice | null;
    /**
     * Check if a vJoy device id exists
     * @param {Number} id
     * @returns {Boolean}
     */
    static exists(id: number): boolean;
    /**
     * Check the status of a vJoy device
     * @param {Number} id
     * @returns {String}
     */
    static status(id: number): "busy" | "missing" | "free" | "acquired" | "unknown";
    /**
     * Check if a vJoy device supports Force Feedback
     * @param {Number} id
     * @returns {Boolean}
     */
    static ffbSupported(id: number): boolean;
    /**
     * Get an object containing information about the supported FFB effect types
     * @param {Number} id
     * @returns {Object}
     */
    static getFFBEffects(id: number): object;

    constructor(id: any);
    get id(): number;
    get initialized(): boolean;
    get buttons(): Readonly<Record<number, vJoyButton>>;
    get discretePOV(): Readonly<Record<number, vJoyDiscretePOV>>;
    get continuousPOV(): Readonly<Record<number, vJoyContinuousPOV>>;
    get axes(): Readonly<Record<AxisName, vJoyAxis>>;
    get status(): string;
    get ffbSupported(): boolean;
    get ffbEffects(): any;

    /**
     * Initializes the device by checking its status and acquriring it if possible.
     * Returns true if the initialization was successful.
     * @returns {Boolean}
     */
    initialize(): boolean;
    /**
     * Query the driver for configured axes, buttons and POV switches.
     * This also resets all button and POV values
     */
    updateInputs(): void;
    /**
     * Sets all buttons to not pressed
     * @returns {Boolean}
     */
    resetButtons(): boolean;
    /**
     * Relinquishes the device. Do not forget to relinquish a device if you want other feeders to access it.
     */
    free(): void;
    /**
     * Enables the emission of Force Feedback events
     */
    enableFFBEvents(): void;
    /**
     * Disables the emission of Force Feedback events
     */
    disableFFBEvents(): void;
}

export = vJoyDevice;