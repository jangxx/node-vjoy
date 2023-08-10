export = vJoyButton;
declare class vJoyButton {
    constructor(parent: any, buttonId: any);
    _parent: any;
    _id: any;
    _pressed: boolean;
    get id(): any;
    get value(): boolean;
    /**
     * Reset the internal value of the button abstraction
     */
    _reset(): void;
    /**
     * Set this button to be pressed or not pressed
     * @param {Boolean} value
     * @returns {Boolean}
     */
    set(value: boolean): boolean;
}
