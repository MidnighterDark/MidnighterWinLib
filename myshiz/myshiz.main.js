import * as import_myjslib from "../my-library-js-custom/my-library-js-custom.js";
var clicks = Number(0);
var whatTheUserEnteredOnThePage = String();
var isCollectUserInput = false;
const myjslib_init = new myjslib();
document.addEventListener("click", () => {
	if (myjslib_init.checkDOMLoaded() && isCollectUserInput) {
		//clicks++;
	}
});
document.addEventListener("keydown", (e) => {
	if (myjslib_init.checkDOMLoaded() && isCollectUserInput) {
		// if (whatTheUserEnteredOnThePage.length >= 512) {
		// 	whatTheUserEnteredOnThePage = String();
		// }
		// whatTheUserEnteredOnThePage +=
		// 	"\nnew key entered: " +
		// 	e.key +
		// 	". on: " +
		// 	String(new Date().toString());
	}
});
export function howManyUserClickOnMouseButtons() {
	return Number(clicks);
}
window.howManyUserClickOnMouseButtons = howManyUserClickOnMouseButtons;
export function getWhatTheUserEnteredOnThePageData() {
	return String(whatTheUserEnteredOnThePage);
}
window.getWhatTheUserEnteredOnThePageData = getWhatTheUserEnteredOnThePageData;
