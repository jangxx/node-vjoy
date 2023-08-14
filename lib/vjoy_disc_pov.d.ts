export = vJoyDiscretePOV;
declare class vJoyDiscretePOV {
    constructor(parent: any, povId: any);
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
