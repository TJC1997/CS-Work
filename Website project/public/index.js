//this is index.js
var addpostbutton = document.getElementById('add-post-button');
var createpostbutton = document.getElementById('create-post-button');
var cancelpostbutton = document.getElementById('cancel-post-button');
var usernamebutton = document.getElementById('change-username-button');
var createuserbutton = document.getElementById('confirm-username-change');
var canceluserbutton = document.getElementById('cancel-username-change');
var addcommentbutton = document.getElementsByClassName('comment-button');
var createcommentbutton = document.getElementById('create-comment-button');
var cancelcommentbutton = document.getElementById('cancel-comment-button');
var dislikebutton = document.getElementsByClassName('dislike-button');
var content = document.getElementById('content');
var newpostcontainer = document.getElementById('add-post-container');
var usernamecontainer = document.getElementById('change-username-container');
var newcommentcontainer = document.getElementById('add-comment-container');
var check;
var postbackdrop=document.getElementById('add-post-container');
var commentbackdrop=document.getElementById('add-comment-container');
var usernamebackdrop=document.getElementById('change-username-container');
updatebutton();

function updatebutton(){
	addpostbutton.addEventListener('click', function () {
		var a=commentbackdrop.classList.contains('masked') && usernamebackdrop.classList.contains('masked');
		if(a)
		{
			show(newpostcontainer, content);
		}
	});

	createpostbutton.addEventListener('click', create);

	cancelpostbutton.addEventListener('click', function () {
		cancel(content, newpostcontainer);
	});

	usernamebutton.addEventListener('click', function () {
		var a=commentbackdrop.classList.contains('masked') && postbackdrop.classList.contains('masked');
		if(a)
		{
			show(usernamecontainer, content);
		}
	});

	createuserbutton.addEventListener('click', username);
	canceluserbutton.addEventListener('click', function () {
		cancel(content, usernamecontainer);
	});

	for (var i = 0; i < addcommentbutton.length; i++) {
		addcommentbutton[i].addEventListener('click', function () {
			var a=postbackdrop.classList.contains('masked') && usernamebackdrop.classList.contains('masked');
			if(a)
			{
				show(newcommentcontainer, content, this);
			}
		});
	}
	createcommentbutton.addEventListener('click', comment);
	cancelcommentbutton.addEventListener('click', function () {
		cancel(content, newcommentcontainer);
	});

	for (var i = 0; i < dislikebutton.length; i++) {
		dislikebutton[i].addEventListener('click', function () {
			dislike(this);
		});
	}
}
function show(show, hide, ele) {
	show.classList.remove('masked');
	show.classList.add('center');
	hide.classList.add('masked');
	if (ele) {
		check = ele.parentElement.parentElement.parentElement; //get the grand gand parent of comment or dislike button
	}
}

function cancel(show, hide) {
	hide.classList.add('masked');
	hide.classList.remove('center');
	show.classList.remove('masked');
	clean();
}

function create() //create a new post,need a template
{
	updatebutton();
	var title = document.getElementById('post-title-input').value; //the title of the post
	var textcontent = document.getElementById('post-content-input').value; //the content of the post
	var user=document.getElementById('change-username-button').textContent;
	if (title && textcontent) {
		var postRequest = new XMLHttpRequest();
		var postURL="/addPost";
		postRequest.open('POST',postURL);
		var args={
			postTitle:title,
			userName:user,
			postContent:textcontent,
			NumDislikes: "0"
		}
		var requestBody=JSON.stringify(args);
		postRequest.setRequestHeader('Content-Type','application/json');
		postRequest.addEventListener('load', function (event) {
			if (event.target.status !== 200) {
			  alert("Error storing photo in database:\n\n\n" + event.target.response);
			} else {
				var postcontainer=document.getElementById('posts');
				var html=Handlebars.templates.content_container(args);
				postcontainer.insertAdjacentHTML('beforeend',html);
			}
		});
		postRequest.send(requestBody);
		//you need to rend a new post into the page here
		cancel(content, newpostcontainer);
	} else {
		alert("You must fill all blanks!");
	}
}

function clean() {
	var all = document.getElementsByTagName('input');
	for (var i = 0; i < all.length; i++) {
		all[i].value = "";
	}
}

function username() {
	var name = document.getElementById('username-input').value;
	if (name) {
		document.getElementById('change-username-button').textContent = name;
		cancel(content, usernamecontainer);
	} else {
		alert("You must fill in all fields to continue.");
	}
}

function comment() //the second template for user comment
{
	var name = document.getElementById('change-username-button').textContent; //username
	var textcontent = document.getElementById('comment-input').value; //the comment made by user
	if (textcontent) {
		var allcomment = check.getElementsByTagName('div')[5]; //i have already found the comment container for you
		var parent=allcomment.parentElement;
		var text=parent.getElementsByClassName('post-title')[0].textContent;
		var args={
			commentUsername:name,
			commentContent:textcontent,
			text:text
		}
		var html=Handlebars.templates.comment(args);
		allcomment.insertAdjacentHTML('beforeend',html);
		
		var postRequest = new XMLHttpRequest();
		var postURL="/addcomment";
		postRequest.open('POST',postURL);
		var requestBody=JSON.stringify(args);
		postRequest.setRequestHeader('Content-Type','application/json');
		postRequest.send(requestBody);
		//you need to add a comment to the post here
		cancel(content, newcommentcontainer);
	} else {
		alert("You must fill all blanks!");
	}
}

function dislike(ele) {
	var number = ele.getElementsByTagName('div')[0].textContent;
	number = parseInt(number) + 1;
	ele.getElementsByTagName('div')[0].textContent = number;
}
