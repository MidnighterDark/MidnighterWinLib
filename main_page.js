import * as __MYJSLIB from "./my-library-js-custom/my-library-js-custom.js";
//On document loaded
var _current_download_res_select = "n";
var _domLoad = false;
var cdw, cdh;
/**
 * first - news-page's width,
 */
var _reference_widths = {};
function resizeFunc() {
	const cww = Number(
		window
			.getComputedStyle(document.documentElement)
			.width.replace("px", ""),
	);
	const cwh = Number(
		window
			.getComputedStyle(document.documentElement)
			.height.replace("px", ""),
	);
	document.getElementById("icon-button-settings").style.marginLeft =
		String(cww - (512 / 100) * 12) + "px";
	const rbr = document
		.getElementById("background-right-banner")
		.getBoundingClientRect();
	const lbr = document
		.getElementById("background-left-banner")
		.getBoundingClientRect();
	const np = document.getElementById("news-page");
	const np_style = window.getComputedStyle(np);
	const npns = document.getElementById("news-scrollbar");
	const npns_style = window.getComputedStyle(npns);
	np.style.width = String(rbr.left - lbr.right) + String("px");
	npns.style.width =
		String(
			(Number(np_style.width.replace("px", "")) / _reference_widths[0]) *
				1050,
		) + String("px");

	if (rbr.left < lbr.right) {
		document.getElementById("background-right-banner").style.marginTop =
			"250px";
	} else {
		document.getElementById("background-right-banner").style.marginTop =
			"0px";
	}
	const bkg = document.getElementById("main-background-box-of-download-list");
	const dle = document.getElementById("download-list");
	const bkgs = window.getComputedStyle(bkg);
	const nbkgbw = bkg.getBoundingClientRect().right;
	if (cww < nbkgbw) {
		dle.style.marginLeft = String(-300) + "px";
	} else if (cww > 1060) {
		dle.style.marginLeft = String(0) + "px";
	}
}
document.addEventListener("DOMContentLoaded", () => {
	_domLoad = true;
	cdw = Number(
		getComputedStyle(document.documentElement).width.replace("px", ""),
	);
	cdh = Number(
		getComputedStyle(document.documentElement).height.replace("px", ""),
	);
	document.getElementById("icon-button-settings").style.marginLeft =
		String(cdw - (512 / 100) * 12) + "px";
	const news_page = document.getElementById("news-page");
	document.getElementById("download-list").style.display = "none";
	document
		.getElementById("close-download-list")
		.addEventListener("mouseenter", () => {
			document.getElementById("close-download-list").src =
				"res/imgclosered.png";
		});
	document
		.getElementById("close-download-list")
		.addEventListener("mouseleave", () => {
			document.getElementById("close-download-list").src =
				"res/imgclose.png";
		});
	document
		.getElementById("close-download-list")
		.addEventListener("mousedown", () => {
			const c = document.getElementById("download-list");
			c.style.animation = "animclose 0.2s forwards";
			setTimeout(() => {
				c.style.display = "none";
				c.style.animation = "none";
			}, 250);
		});
	document
		.getElementById("icon-button-settings")
		.addEventListener("mousedown", (e) => {
			setTimeout(() => {
				const swe = document.getElementById("settings-list");
				swe.style.display = "block";
				swe.style.animation = "animopen 0.2s forwards";
				swe.style.transform =
					String("translate(") +
					String(e.pageX - 222) +
					"px" +
					String(",") +
					String(e.pageY - 12) +
					"px" +
					String(")");
			}, 25);
		});
	document.addEventListener("mousedown", (e) => {
		const swe = document.getElementById("settings-list");
		if (
			window.getComputedStyle(swe).display != "none" &&
			!containsInRect(e.pageX, e.pageY, swe.getBoundingClientRect())
		) {
			swe.style.display = "none";
		}
	});
	document.getElementsByTagName("COPYRIGHT")[0].innerHTML =
		new Date().getFullYear().toString() +
		String(" Midnighter все права защищены.");

	_reference_widths[0] = Number(
		window.getComputedStyle(news_page).width.replace("px", ""),
	);
	resizeFunc();
	//Resize
	window.addEventListener("resize", () => {
		resizeFunc();
	});
});
export function checkURL(url) {
	fetch(url, { method: "HEAD" })
		.then((response) => {
			if (response.ok) {
				location.href = url;
				console.log("Downloading...");
			} else {
				alert("Временно недоступен!!!");
				console.log(
					String("Can't find file from: ") +
						String(url) +
						String("!!!"),
				);
			}
		})
		.catch((error) => {
			console.error("Ошибка при проверке файла:", error);
		});
}
window.checkURL = checkURL;
export function set_cdrs(newval) {
	if (_domLoad == true) {
		_current_download_res_select = newval;
		document.getElementById("_download_list_link_zip_text").innerText =
			"Download " + _current_download_res_select + ".zip";
		document.getElementById("_download_list_link_rar_text").innerText =
			"Download " + _current_download_res_select + ".rar";
		document.getElementById("download-list").style.display = "block";
		document.getElementById("download-list").style.animation =
			"animopen 0.2s forwards";
	}
}
window.set_cdrs = set_cdrs;
export function __get_current_download_res_select() {
	return _current_download_res_select;
}
window.__get_current_download_res_select = __get_current_download_res_select;
export function __enable_dark_theme(is) {
	const bb = document.getElementsByTagName("body")[0];
	const nsl = document.getElementById("news-scrollbar");
	const sl = document.getElementById("settings-list-background");
	let cp;
	if (is == true) {
		cp = "rgb(25, 25, 25)";
	} else if (is == false) {
		cp = "rgb(250, 250, 250)";
	} else {
		console.log("Error parametr 'is' has incorrect value!!!");
	}
	bb.style.backgroundColor = cp;
	nsl.style.backgroundColor = cp;
	sl.style.backgroundColor = cp;
}
window.__enable_dark_theme = __enable_dark_theme;
