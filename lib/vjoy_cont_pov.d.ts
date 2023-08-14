export = vJoyContinuousPOV;
declare class vJoyContinuousPOV {
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
