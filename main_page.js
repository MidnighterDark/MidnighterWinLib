//On document loaded
var _current_download_res_select = "n";
var _domLoad = false;
/**
 * first - news-page's width,
 */
var _reference_widths = {};
document.addEventListener("DOMContentLoaded", () => {
	_domLoad = true;
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
	document.getElementsByTagName("COPYRIGHT")[0].innerHTML =
		new Date().getFullYear().toString() +
		String(" Midnighter все права защищены.");

	_reference_widths[0] = Number(
		window.getComputedStyle(news_page).width.replace("px", ""),
	);
	//Resize
	window.addEventListener("resize", () => {
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
				(Number(np_style.width.replace("px", "")) /
					_reference_widths[0]) *
					1050,
			) + String("px");

		if (rbr.left < lbr.right) {
			document.getElementById("background-right-banner").style.marginTop =
				"250px";
		} else {
			document.getElementById("background-right-banner").style.marginTop =
				"0px";
		}
	});
});
function checkURL(url) {
	location.href = url;
}
function set_cdrs(newval) {
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
