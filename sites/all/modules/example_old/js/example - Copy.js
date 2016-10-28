$(document).ready(function(){
	//var url      = window.location.href; 
	//var currenturl = jQuery(location).attr('search');
	var url2 = (window.location.search).replace("?", "");
	alert(url2);
	
	$.ajax({
		
    headers: {'Content-Type': 'application/x-www-form-urlencoded' },
	type: "POST",
	url: "https://pub.orcid.org/oauth/token",
    data : "client_id=APP-056GSP3J5RDS9KCM&client_secret=f5fcc22e-bd05-4c58-88c3-92d02be078dd&grant_type=authorization_code&redirect_uri=http://localhost/drupal/examples/example/&"+url2,
	
    success: function (response) {
	   alert(response.access_token);
	   alert(response.orcid);
       console.log(response);
    },
    error: function (error) {
		alert(url2);
       console.log(error);
    }
	}); 
 		
 });


 
 
 
 