export = vJoyAxis;
declare class vJoyAxis {
    constructor(parent: any, axisId: any);
    _parent: any;
    _id: any;
    _value: number;
    get id(): any;
    get value(): number;
    /**
     * Reset the internal value of the POV abstraction
     */
    _reset(): void;
    /**
     * Set the value of the axis between 1 and 32769 (0x8000)
     * @param {Number} value
     * @returns {Boolean}
     */
    set(value: number): boolean;
}
