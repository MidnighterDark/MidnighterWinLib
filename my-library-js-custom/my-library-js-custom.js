var data = {};
data[0] = false;
data[1] = false;
document.addEventListener("DOMContentLoaded", () => {
	data[0] = true;
});
document.addEventListener("focusin", () => {
	data[1] = true;
});
document.addEventListener("focusout", () => {
	data[1] = false;
});
export class myjslib {
	checkDOMLoaded() {
		return Boolean(data[0]);
	}
	checkFocus() {
		return Boolean(data[1]);
	}
}
window.myjslib = myjslib;
function includeJsScript(url) {
	var script = document.createElement("script");
	script.src = url;
	document.getElementsByTagName("head")[0].appendChild(script);
}
function containsInRect(x, y, rect) {
	if (
		x >= rect.left &&
		x <= rect.right &&
		y >= rect.top &&
		y <= rect.bottom
	) {
		return true;
	}
	return false;
}
window.containsInRect = containsInRect;
