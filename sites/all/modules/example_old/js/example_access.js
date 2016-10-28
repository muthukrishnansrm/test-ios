$(document).ready(function(){
	$.ajax({
    headers: {'Content-Type': 'application/json; qs=3;charset=UTF-8', 'Authorization': 'Bearer a3c96773-3edc-4398-86bc-3c066e612ce1'},
	type: "GET",
	url: "https://pub.orcid.org/v1.2/search/orcid-bio/?q=orcid:0000-0001-7939-7167",
	dataType: "jsonp",
	//data: JSON.stringify(this),
    success: function (data) {
		//alert(data.access_token);
      console.log(data);
	 // console.log(JSON.stringify({duration: data}));
    //  console.log(JSON.stringify(data.personal-details)); 
		// console.dir(data);
		// console.log(data);
	//	console.log('Item: ',data)
		
    },
    error: function (error) {
		
		alert("Failed");
       console.log(error);
    }
	}); 
	 		
 });