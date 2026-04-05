//On document loaded
var _current_download_res_select = "n";
var _domLoad = false;
document.addEventListener("DOMContentLoaded", () => {
	_domLoad = true;
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
	//Resize
	document.addEventListener("resize", () => {});
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
