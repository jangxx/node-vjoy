export = vJoyDevice;
declare class vJoyDevice {
    /**
     * Convenience method to create and initialize a new vJoyDevice
     * @param {Number} id
     * @return {vJoyDevice}
     */
    static create(id: number): vJoyDevice;
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
    static status(id: number): string;
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
    static getFFBEffects(id: number): any;
    constructor(id: any);
    _id: any;
    _initialized: boolean;
    _axes: {};
    _buttons: {};
    _discretePOV: {};
    _continuousPOV: {};
    get id(): any;
    get initialized(): boolean;
    get buttons(): Readonly<{}>;
    get discretePOV(): Readonly<{}>;
    get continuousPOV(): Readonly<{}>;
    get axes(): Readonly<{}>;
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
    free(): any;
    /**
     * Enables the emission of Force Feedback events
     */
    enableFFBEvents(): void;
    /**
     * Disables the emission of Force Feedback events
     */
    disableFFBEvents(): void;
}
