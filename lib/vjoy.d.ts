type RemovalCallbackData = {
	removed: boolean,
	first: boolean
}

type DriverMatchData = {
	matches: boolean,
	dll_version: number,
	drv_version: number,
}

export type AxisName = "X" | "Y" | "Z" | "Rx" | "Ry" | "Rz" | "Slider0" | "Slider1" | "Wheel" | "POV";

export module vJoy {
	function isEnabled(): boolean;
	function version(): number;
	function productString(): string;
	function manufacturerString(): string;
	function serialString(): string;
	function driverMatch(): DriverMatchData;
	function maxDevices(): number;
	function existingDevices(): number;
	function registerRemovalCB(callback: (evt: RemovalCallbackData) => void): void;
	const axis: readonly AxisName[];
}