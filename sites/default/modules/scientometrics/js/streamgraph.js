// "use strict";

var _STREAMGRAPH = {urls:{}, data:{years:{},authors:{},titles:{},countries:{}}};
var sciento_sparql_endpoint = "http://lod.fuzzyinsights.com:3030/fuzzyinsights-beta"
_STREAMGRAPH.endpoint = sciento_sparql_endpoint;
_STREAMGRAPH.limit = 20;
_STREAMGRAPH.loadcnt = 0;
_STREAMGRAPH.container = null;
var sciento_color = "#0035ff";
var url = sciento_sparql_endpoint+"/query?query=PREFIX+dcterms%3A+%3Chttp%3A%2F%2Fpurl.org%2Fdc%2Fterms%2F%3E%0D%0APREFIX+rdfs%3A+%3Chttp%3A%2F%2Fwww.w3.org%2F2000%2F01%2Frdf-schema%23%3E%0D%0APREFIX+foaf%3A+%3Chttp%3A%2F%2Fxmlns.com%2Ffoaf%2F0.1%2F%3E%0D%0Aselect+%3Fkey+%28count%28%3Fdate%29+AS+%3Fvalue%29+%3Fdate+where%7B%0D%0A++%7Bselect+distinct+%3Fpaper+%7B%3Fpaper+dcterms%3Acreated+%3Fo%7D%7D%0D%0A++%3Fpaper+foaf%3Atopic+%3Fkeywords.%0D%0A++%3Fkeywords+rdfs%3Alabel+%3Fkey.%0D%0A++%3Fpaper+dcterms%3Acreated+%3Fdate%0D%0A++%7Bselect+%3Fkey+%28count%28%3Fkey%29+as+%3Fcnt2%29+where+%7B%0D%0A++++%3Fpaper+foaf%3Atopic+%3Fkeywords.%0D%0A++++%3Fkeywords+rdfs%3Alabel+%3Fkey++%0D%0A++++%7Dgroup+by+%3Fkey+order+by+desc%28%3Fcnt2%29+limit+20%0D%0A++%7D%0D%0A%7Dgroup+by+%3Fkey+%3Fdate+order+by+asc%28%3Fkey%29+%3Fdate&output=csv";

var urlsYears = sciento_sparql_endpoint+"/query?query=PREFIX+dcterms%3A+%3Chttp%3A%2F%2Fpurl.org%2Fdc%2Fterms%2F%3E%0D%0APREFIX+rdfs%3A+%3Chttp%3A%2F%2Fwww.w3.org%2F2000%2F01%2Frdf-schema%23%3E%0D%0APREFIX+foaf%3A+%3Chttp%3A%2F%2Fxmlns.com%2Ffoaf%2F0.1%2F%3E%0D%0Aselect+%3Fkey+%3Fdate+%28count%28%3Fkey%29+as+%3Fcount%29+where%7B%0D%0A++%7Bselect+distinct+%3Fpaper+%7B%3Fpaper+dcterms%3Acreated+%3Fo%7D%7D%0D%0A++%3Fpaper+foaf%3Atopic+%3Fkeywords.%0D%0A++%3Fkeywords+rdfs%3Alabel+%3Fkey.%0D%0A++%3Fpaper+dcterms%3Acreated+%3Fdate%0D%0A++%7Bselect+%3Fkey+%28count%28%3Fkey%29+as+%3Fcnt2%29+where+%7B%0D%0A++%09%3Fpaper+foaf%3Atopic+%3Fkeywords.%0D%0A++%09%3Fkeywords+rdfs%3Alabel+%3Fkey++%0D%0A++%09%7Dgroup+by+%3Fkey+order+by+desc%28%3Fcnt2%29+limit+20%0D%0A++%7D%0D%0A%7Dgroup+by+%3Fkey+%3Fdate+order+by+%3Fkey+%3Fdate&output=json";

var urlsAuthors = sciento_sparql_endpoint+"/query?query=PREFIX+dcterms%3A+%3Chttp%3A%2F%2Fpurl.org%2Fdc%2Fterms%2F%3E%0D%0APREFIX+rdfs%3A+%3Chttp%3A%2F%2Fwww.w3.org%2F2000%2F01%2Frdf-schema%23%3E%0D%0APREFIX+foaf%3A+%3Chttp%3A%2F%2Fxmlns.com%2Ffoaf%2F0.1%2F%3E%0D%0Aselect+%3Fkey+%3Fdate+%3Fauthor+%3Fauthoruri%28count%28%3Fauthor%29+as+%3Fcount%29+where%7B%0D%0A++%7Bselect+distinct+%3Fpaper+%7B%3Fpaper+dcterms%3Acreated+%3Fo%7D%7D%0D%0A++%3Fpaper+foaf%3Atopic+%3Fkeywords.%0D%0A++%3Fkeywords+rdfs%3Alabel+%3Fkey.%0D%0A++%3Fpaper+dcterms%3Acreator+%3Fauthoruri.%0D%0A++%3Fauthoruri+rdfs%3Alabel+%3Fauthor.%0D%0A++%3Fpaper+dcterms%3Acreated+%3Fdate%0D%0A++%7Bselect+%3Fkey+%28count%28%3Fkey%29+as+%3Fcnt2%29+where+%7B%0D%0A++++%3Fpaper+foaf%3Atopic+%3Fkeywords.%0D%0A++++%3Fkeywords+rdfs%3Alabel+%3Fkey++%0D%0A++++%7Dgroup+by+%3Fkey+order+by+desc%28%3Fcnt2%29+limit+20%0D%0A++%7D%0D%0A%7Dgroup+by+%3Fkey+%3Fdate+%3Fauthor+%3Fauthoruri+order+by+%3Fkey+%3Fdate+desc%28%3Fcount%29&output=json";

var urlsTitles = sciento_sparql_endpoint+"/query?query=PREFIX+dcterms%3A+%3Chttp%3A%2F%2Fpurl.org%2Fdc%2Fterms%2F%3E%0D%0APREFIX+rdfs%3A+%3Chttp%3A%2F%2Fwww.w3.org%2F2000%2F01%2Frdf-schema%23%3E%0D%0APREFIX+foaf%3A+%3Chttp%3A%2F%2Fxmlns.com%2Ffoaf%2F0.1%2F%3E%0D%0Aselect+%3Fkey+%3Fdate+%3Ftitle+%3Fpaper+where%7B%0D%0A++%7Bselect+distinct+%3Fpaper+%7B%3Fpaper+dcterms%3Acreated+%3Fo%7D%7D%0D%0A++%3Fpaper+foaf%3Atopic+%3Fkeywords.%0D%0A++%3Fkeywords+rdfs%3Alabel+%3Fkey.%0D%0A++%3Fpaper+rdfs%3Alabel+%3Ftitle.%0D%0A++%3Fpaper+dcterms%3Acreated+%3Fdate%0D%0A++%7Bselect+%3Fkey+%28count%28%3Fkey%29+as+%3Fcnt2%29+where+%7B%0D%0A++++%3Fpaper+foaf%3Atopic+%3Fkeywords.%0D%0A++++%3Fkeywords+rdfs%3Alabel+%3Fkey++%0D%0A++++%7Dgroup+by+%3Fkey+order+by+desc%28%3Fcnt2%29+limit+20%0D%0A++%7D%0D%0A%7Dgroup+by+%3Fkey+%3Fdate+%3Ftitle+%3Fpaper+order+by+%3Fkey+%3Fdate+%3Ftitle&output=json";

var urlsCountries = sciento_sparql_endpoint+"/query?query=PREFIX+dcterms%3A+%3Chttp%3A%2F%2Fpurl.org%2Fdc%2Fterms%2F%3E%0D%0APREFIX+rdfs%3A+%3Chttp%3A%2F%2Fwww.w3.org%2F2000%2F01%2Frdf-schema%23%3E%0D%0APREFIX+foaf%3A+%3Chttp%3A%2F%2Fxmlns.com%2Ffoaf%2F0.1%2F%3E%0D%0APREFIX+schema%3A+%3Chttp%3A%2F%2Fschema.org%2F%3E%0D%0Aselect+%3Fkey+%3Fdate+%3Forg+%28count%28%3Forg%29+as+%3Fcount%29+where%7B%0D%0A++%7Bselect+distinct+%3Fpaper+%7B%3Fpaper+dcterms%3Acreated+%3Fo%7D%7D%0D%0A++%3Fpaper+foaf%3Atopic+%3Fkeywords.%0D%0A++%3Fkeywords+rdfs%3Alabel+%3Fkey.%0D%0A++%3Fpaper+dcterms%3Acreator+%3Fauthor.%0D%0A++%3Fauthor+schema%3AaddressCountry+%3Forg.%0D%0A++%3Fpaper+dcterms%3Acreated+%3Fdate%0D%0A++%7Bselect+%3Fkey+%28count%28%3Fkey%29+as+%3Fcnt2%29+where+%7B%0D%0A++++%3Fpaper+foaf%3Atopic+%3Fkeywords.%0D%0A++++%3Fkeywords+rdfs%3Alabel+%3Fkey++%0D%0A++++%7Dgroup+by+%3Fkey+order+by+desc%28%3Fcnt2%29+limit+20%0D%0A++%7D%0D%0A%7Dgroup+by+%3Fkey+%3Fdate+%3Forg+order+by+%3Fkey+%3Fdate+%3Forg&output=json";

var urldetails = sciento_sparql_endpoint+"/query?query=PREFIX+dcterms%3A+%3Chttp%3A%2F%2Fpurl.org%2Fdc%2Fterms%2F%3E%0D%0APREFIX+rdfs%3A+%3Chttp%3A%2F%2Fwww.w3.org%2F2000%2F01%2Frdf-schema%23%3E%0D%0APREFIX+foaf%3A+%3Chttp%3A%2F%2Fxmlns.com%2Ffoaf%2F0.1%2F%3E%0D%0APREFIX+schema%3A+%3Chttp%3A%2F%2Fschema.org%2F%3E%0D%0Aselect+%3Fkey+%3Ftitle+%3Fdate+%3Fauthorname+where%7B%0D%0A++%7Bselect+distinct+%3Fpaper+%7B%3Fpaper+dcterms%3Acreated+%3Fo%7D%7D%0D%0A++%3Fpaper+foaf%3Atopic+%3Fkeywords.%0D%0A++%3Fkeywords+rdfs%3Alabel+%3Fkey.%0D%0A++%3Fpaper+rdfs%3Alabel+%3Ftitle.%0D%0A++%3Fpaper+dcterms%3Acreator+%3Fauthor.%0D%0A++%3Fauthor+rdfs%3Alabel+%3Fauthorname.%0D%0A++%3Fpaper+dcterms%3Acreated+%3Fdate%0D%0A++%7Bselect+%3Fkey+%28count%28%3Fkey%29+as+%3Fcnt2%29+where+%7B%0D%0A++++%3Fpaper+foaf%3Atopic+%3Fkeywords.%0D%0A++++%3Fkeywords+rdfs%3Alabel+%3Fkey++%0D%0A++++%7Dgroup+by+%3Fkey+order+by+desc%28%3Fcnt2%29+limit+20%0D%0A++%7D%0D%0A%7Dorder+by+%3Fkey&format=json&timeout=0&debug=on";
console.log(urlsYears);

var pro, yr;
var a ;

(function($){
		Drupal.behaviors.scientometrics = {
  			attach: function (context, settings) {
  				$('#content').html("");
    			$('#content', context).append('<div id="sciento_app"></div>');
          var text = "";
          // _STREAMGRAPH.container = container;
          // a = container;
          text += '<div class="module-info" style="width:100%;text-align:left;color:#fff">This <i>Stream Graph</i> shows the top 20 keywords from the Journal of Intelligent and fuzzy systems.  Hover over the <i>Stream Graph</i> to view the Keyword along with the Authors and Papers that include the keyword as well as the count of that keyword per year and the country of the author(s) that used the selected keyword.  Click on a stream to <i>lock it</i> and scroll through the information boxes below.</div>';
          text += '<div id="sg_container_lock" style="position:absolute;height:250px;width:1024px;margin-left:50%;left:-512px;top:180px;z-index:100;display:none;"></div>';
          text += '<div id="sg_container" style="position:relative;height:100%;">';

          text += '<div style="height:30px;overflow:hidden;margin-left:20px;" id="timewrapper"></div>';
          text += '<div style="clear:both;overflow:hidden;margin-top:5px;" class="sg_chart" id="sg_chart"></div>';

          text += '<div id="wrapperAuthors" style="float:left;height:200px;width:25%;overflow-x:hidden;overflow-y:auto;margin:2px;">';
          text += '<div style="border-radius:3px;margin-top:5px;padding:3px 10px;color:#fff;font-weight:bold;background-color:'+sciento_color+';width:100%;font-size:1.0em;">Authors <span class="authoryear"></span></div>';
          text += '<div id="wrapperAuthorsContent" style="color:#fff;font-size:0.9em;overflow:auto;"></div></div>';

          text += '<div id="wrapperPapers" style="float:left;height:200px;width:58%;overflow-x:hidden;overflow-y:auto;margin:2px;">';
          text += '<div style="border-radius:3px;margin-top:5px;padding:3px 10px;color:#fff;font-weight:bold;background-color:'+sciento_color+';width:100%;font-size:1.0em;">Papers <span class="authoryear"></span></div>';
          text += '<div id="wrapperPaperContent" style="color:#fff;font-size:0.9em;overflow:auto;"></div></div>';

          text += '<div id="wrapperYears" style="float:left;height:200px;width:15%;overflow-x:hidden;overflow-y:auto;margin:2px;">';
          text += '  <div style="border-radius:3px;margin-top:5px;padding:3px 10px;color:#fff;font-weight:bold;background-color:'+sciento_color+';width:100%;font-size:1.0em;">Years</div>';
          text += '  <div id="wrapperYearsContent" style="color:#fff;font-size:0.9em;"></div></div>';

          text += '<div style="height:300px;overflow:hidden;width:680px;" id="sg_map"></div>';

          text += '<div style="opacity: 0.9;position:absolute;top:0px;left:0px;width:110%;height:120%;z-index:3;background-color:#000;overflow:hidden" id="loading"></div>';
          text += '<div id="loadingimg" style="left:50%;top:50%;margin-left:-60px;margin-top:-50px;position:absolute;z-index:4;text-align:center;font-size:1.2em;color:#fff;"><img src="http://disambiguation.dd:8083/sites/disambiguation.dd/files/img/loading.gif"/><br/><br/>Loading streamgraph</div></div>';
          $('#sciento_app').html(text);
  			}
		};
})(jQuery);

load_sciento_streamgraph();

// Global variables
// var _STREAMGRAPH = {urls:{}, data:{years:{},authors:{},titles:{},countries:{}}};
// var sciento_sparql_endpoint = "http://lod.fuzzyinsights.com:3030/fuzzyinsights-beta"
// _STREAMGRAPH.endpoint = sciento_sparql_endpoint;
// _STREAMGRAPH.limit = 20;
// _STREAMGRAPH.loadcnt = 0;
// _STREAMGRAPH.container = null;
// var sciento_color = "#0035ff";


// var pro, yr;
// var a ;
// _STREAMGRAPH.setUpHTMLContainers = function(container) {
 
//     var content = "";
//     _STREAMGRAPH.container = container;
//     a = container;
//     content += '<div class="module-info" style="width:100%;text-align:left;color:#fff">This <i>Stream Graph</i> shows the top 20 keywords from the Journal of Intelligent and fuzzy systems.  Hover over the <i>Stream Graph</i> to view the Keyword along with the Authors and Papers that include the keyword as well as the count of that keyword per year and the country of the author(s) that used the selected keyword.  Click on a stream to <i>lock it</i> and scroll through the information boxes below.</div>';
//     content += '<div id="sg_container_lock" style="position:absolute;height:250px;width:1024px;margin-left:50%;left:-512px;top:180px;z-index:100;display:none;"></div>';
//     content += '<div id="sg_container" style="position:relative;height:100%;">';



//     content += '<div style="height:30px;overflow:hidden;margin-left:20px;" id="timewrapper"></div>';
//     content += '<div style="clear:both;overflow:hidden;margin-top:5px;" class="sg_chart" id="sg_chart"></div>';

//     content += '<div id="wrapperAuthors" style="float:left;height:200px;width:25%;overflow-x:hidden;overflow-y:auto;margin:2px;">';
//     content += '<div style="border-radius:3px;margin-top:5px;padding:3px 10px;color:#fff;font-weight:bold;background-color:'+sciento_color+';width:100%;font-size:1.0em;">Authors <span class="authoryear"></span></div>';
//     content += '<div id="wrapperAuthorsContent" style="color:#fff;font-size:0.9em;overflow:auto;"></div></div>';

//     content += '<div id="wrapperPapers" style="float:left;height:200px;width:58%;overflow-x:hidden;overflow-y:auto;margin:2px;">';
//     content += '<div style="border-radius:3px;margin-top:5px;padding:3px 10px;color:#fff;font-weight:bold;background-color:'+sciento_color+';width:100%;font-size:1.0em;">Papers <span class="authoryear"></span></div>';
//     content += '<div id="wrapperPaperContent" style="color:#fff;font-size:0.9em;overflow:auto;"></div></div>';

//     content += '<div id="wrapperYears" style="float:left;height:200px;width:15%;overflow-x:hidden;overflow-y:auto;margin:2px;">';
//     content += '  <div style="border-radius:3px;margin-top:5px;padding:3px 10px;color:#fff;font-weight:bold;background-color:'+sciento_color+';width:100%;font-size:1.0em;">Years</div>';
//     content += '  <div id="wrapperYearsContent" style="color:#fff;font-size:0.9em;"></div></div>';

//     content += '<div style="height:300px;overflow:hidden;width:680px;" id="sg_map"></div>';

//     content += '<div style="opacity: 0.9;position:absolute;top:0px;left:0px;width:110%;height:120%;z-index:3;background-color:#000;overflow:hidden" id="loading"></div>';
//     content += '<div id="loadingimg" style="left:50%;top:50%;margin-left:-60px;margin-top:-50px;position:absolute;z-index:4;text-align:center;font-size:1.2em;color:#fff;"><img src="http://disambiguation.dd:8083/sites/disambiguation.dd/files/img/loading.gif"/><br/><br/>Loading streamgraph</div></div>';
//     $('#sciento_app').html(content);
//     // console.log($(container));
// }


function streamgraphError(a,b,c) {
  alert('error');
}

function checkLoadCount() {
    if (_STREAMGRAPH.loadcnt == 4) {
        $('#loading').fadeOut();
        $('#loadingimg').fadeOut();
        _STREAMGRAPH.loadcnt = 0;
    }
}

function loadYears() {
  console.log(urlsYears);
  $.ajax({
      type: "GET",
      url: urlsYears,
      dataType: "json",
      success: function(data) {
          console.log(data);
          var x = data.results.bindings;
          for(var i=0;i<x.length;i++) {
              var a = x[i].date.value;
              if (_STREAMGRAPH.data.years[x[i].key.value]) {
                  _STREAMGRAPH.data.years[x[i].key.value][a] = x[i].count.value;

              } else {
                _STREAMGRAPH.data.years[x[i].key.value] = {};
                _STREAMGRAPH.data.years[x[i].key.value][a] = x[i].count.value;
              }
          }
          _STREAMGRAPH.loadcnt++;
          checkLoadCount();
      },
      error: function(a,b,c) {
    streamgraphError(a,b,c);
    _STREAMGRAPH.loadcnt++;
        checkLoadCount();
      }
  });
  console.log(_STREAMGRAPH.loadcnt);
}

function loadAuthors() {
  $.ajax({
      type: "GET",
      url: urlsAuthors,
      dataType: "json",
      success: function(data) {
          // console.log(data);
          var x = data.results.bindings;
          for(var i=0;i<x.length;i++) {
              var a = x[i].date.value;
              if (_STREAMGRAPH.data.authors[x[i].key.value]) {
      if(_STREAMGRAPH.data.authors[x[i].key.value][a])
        _STREAMGRAPH.data.authors[x[i].key.value][a].push([x[i].author.value,x[i].count.value,x[i].authoruri.value]);
      else
        _STREAMGRAPH.data.authors[x[i].key.value][a] = [[x[i].author.value,x[i].count.value,x[i].authoruri.value]];

              } else {
                _STREAMGRAPH.data.authors[x[i].key.value] = [];
                _STREAMGRAPH.data.authors[x[i].key.value][a] = [[x[i].author.value,x[i].count.value,x[i].authoruri.value]];
              }
          }
          _STREAMGRAPH.loadcnt++;
          checkLoadCount();
      },
      error: function(a,b,c) {
    streamgraphError(a,b,c);
    _STREAMGRAPH.loadcnt++;
          checkLoadCount();
      }
  });
}

function loadTitles(){
  $.ajax({
      type: "GET",
      url: urlsTitles,
      dataType: "json",
      success: function(data) {
          // console.log(data);
          var x = data.results.bindings;
          for(var i=0;i<x.length;i++) {
              var a = x[i].date.value;
              if (_STREAMGRAPH.data.titles[x[i].key.value]) {
                  if(_STREAMGRAPH.data.titles[x[i].key.value][a])
        _STREAMGRAPH.data.titles[x[i].key.value][a].push([x[i].title.value,x[i].paper.value]);
      else
        _STREAMGRAPH.data.titles[x[i].key.value][a] = [[x[i].title.value,x[i].paper.value]];
              } else {
                _STREAMGRAPH.data.titles[x[i].key.value] = {};
                _STREAMGRAPH.data.titles[x[i].key.value][a] = [[x[i].title.value,x[i].paper.value]];
              }
          }
          _STREAMGRAPH.loadcnt++;
          checkLoadCount();
      },
      error: function(a,b,c) {
         streamgraphError(a,b,c);
         _STREAMGRAPH.loadcnt++;
         checkLoadCount();
      }
  });
}

function loadCountries() {
  $.ajax({
      type: "GET",
      url: urlsCountries,
      dataType: "json",
      success: function(data) {
          // console.log(data);
          var x = data.results.bindings;
          for(var i=0;i<x.length;i++) {
              var a = x[i].date.value;
              if (_STREAMGRAPH.data.countries[x[i].key.value]) {
      if(_STREAMGRAPH.data.countries[x[i].key.value][a])
        _STREAMGRAPH.data.countries[x[i].key.value][a].push([x[i].org.value,x[i].count.value]);
      else
        _STREAMGRAPH.data.countries[x[i].key.value][a] = [[x[i].org.value,x[i].count.value]];

              } else {
                _STREAMGRAPH.data.countries[x[i].key.value] = [];
                _STREAMGRAPH.data.countries[x[i].key.value][a] = [[x[i].org.value,x[i].count.value]];
              }
          }
          _STREAMGRAPH.loadcnt++;
          checkLoadCount();
      },
      error: function(a,b,c) {
    streamgraphError(a,b,c);
    _STREAMGRAPH.loadcnt++;
        checkLoadCount();
      }
  });
}



// Camel Case that $hiznat
String.prototype.capitalizeFirstLetter = function() {
    return this.replace(/\w\S*/g, function(txt){return txt.charAt(0).toUpperCase() + txt.substr(1).toLowerCase();});
}


// Initialize Module
function load_sciento_streamgraph() {

    // _STREAMGRAPH.setUpHTMLContainers($('#sciento_app'));
    chart(url, "blue");
    // loadDetails(urldetails);
    loadYears();
    loadAuthors();
    loadTitles();
    loadCountries();

    _STREAMGRAPH.map = new Datamap({element: document.getElementById('sg_map'),fills: {defaultFill: "#333"},geographyConfig: {popupOnHover: false}});

    var datearray = [];
    var colorrange = [];
    var authors = {};
    var years = {};
    var title = {};

    $('#sg_chart').click(function() {
      $('#sg_container_lock').show();
      $('#sg_container_lock').mouseout(function() {
        $('#sg_container_lock').hide();
        $('#sg_container_lock').off('mouseout');
      });
    });

}
  
function chart(csvpath, color) {

var format = d3.time.format("%Y");

var width = $("#sg_container").width();
var height = 250;
var mapwidth = $('#sg_map').width();
var a = (width - mapwidth) / 2;
$('#sg_map').css({"margin-left":a+"px"});
//$('#sg_chart').css("width",width - 260);
$('#timewrapper').css('width', width);

var tooltip = d3.select("#sg_container")
    .append("div")
    .attr("class", "remove")
    .style("position", "absolute")
    .style("z-index", "20")
    .style("visibility", "hidden")
    .style("top", "30px")
    .style("left", "55px");

var x = d3.scale.linear() //d3.time.scale()
    .range([0, width]);

var y = d3.scale.linear()
    .range([height-10, 10]);
var sciento_colorbrewer = ["rgb(255,255,178)", "rgb(254,217,118)", "rgb(254,178,76)", "rgb(253,141,60)", "rgb(252,78,42)", "rgb(227,26,28)", "rgb(177,0,38)", "rgb(255,255,204)", "rgb(255,237,160)", "rgb(254,217,118)", "rgb(254,178,76)", "rgb(253,141,60)", "rgb(252,78,42)", "rgb(227,26,28)", "rgb(189,0,38)", "rgb(128,0,38)", "rgb(255,255,204)", "rgb(255,237,160)", "rgb(254,217,118)", "rgb(254,178,76)", "rgb(253,141,60)", "rgb(252,78,42)", "rgb(227,26,28)", "rgb(177,0,38)"];
var z = d3.scale.ordinal().range(sciento_colorbrewer);
var yAxis = d3.svg.axis()
    .scale(y);

var yAxisr = d3.svg.axis()
    .scale(y);

var stack = d3.layout.stack()
    .offset("silhouette") //expand
    .values(function(d) { return d.values; })
    .x(function(d) { return d.date; })
    .y(function(d) { return d.value; });

var nest = d3.nest()
    .key(function(d) { return d.key; });

var area = d3.svg.area()
    .interpolate("cardinal")
    .x(function(d) { 
      return x(d.date); 
    })
    .y0(function(d) { 
        return y(d.y0); 
    })
    .y1(function(d) { return y(d.y0 + d.y); });

// $('#sg_chart').width(width-260);
var svg = d3.select("#sg_chart").append("svg")
    .attr("width", width)
    .attr("height", height)
    .attr("id","streamgraph")
    .attr("viewBox", "0 0 "+width+" "+height)
  .append("g")
    .attr("transform", "translate(" + 0 + "," + 0 + ")");

var dataJSON = {};
var data_years = [];

var graph = d3.csv(csvpath, function(data) {
  data.forEach(function(d) {
    // console.log(d)
    //d.date = format.parse(d.date);
    d.value = +d.value;
      if(!dataJSON[d.key])
          dataJSON[d.key] = {};
      dataJSON[d.key][d.date] = d.value;
      data_years.push(d.date);

  });
  data = backFillData(dataJSON, data_years, ( width-260));
  // console.log(data);
  data.forEach(function(d) {
    //d.date = format.parse(d.date);
    d.date = d.date;
    d.value = +d.value;
  });

 /* var unique = data_years.filter( onlyUnique ); 
  unique.push("2008");
  unique.sort();
  intyears = [];
  for(var prop in unique) {
    intyears.push(parseInt(unique[prop])); 
  } */

/* var xAxis = d3.svg.axis()
    .scale(x)
    .orient("bottom")
    .tickSize(5)
    .tickValues(unique)   // only one tick at max
    .tickFormat(d3.format("d")); */
/* var xAxis = d3.svg.axis()
    .scale(x)
    .orient("bottom")
    .ticks(d3.time.years); */
var xAxis = d3.svg.axis()
    .scale(x).ticks('');
    //.tickValues([0,1,2,3,4,5])
    //.tickFormat(d3.format("dd"));
  
  var layers = stack(nest.entries(data));

  x.domain(d3.extent(data, function(d) { return d.date; }));
  y.domain([0, d3.max(data, function(d) { return d.y0 + d.y; })]);

  var tmp = shuffle(z.range());

  svg.selectAll(".layer")
      .data(layers)
    .enter().append("path")
      .attr("class", "layer")
      .attr("d", function(d) { return area(d.values); })
      .style("fill", function(d, i) { return tmp[i]; }); // replaced "i"


  svg.append("g")
      .attr("class", "x axis")
      .attr("display", "none")
      .attr("transform", "translate(0," + height + ")")
      .call(xAxis);

 /* svg.append("g")
      //.attr("class", "y axis")
      .attr("transform", "translate(" + width + ", 0)")
      .call(Axis.orient("bottom")); */

  svg.selectAll(".layer")
    .attr("opacity", 1)
    .attr("cursor","pointer")
    .on("mouseover", function(d, i) {
      svg.selectAll(".layer").transition()
      .duration(250)
      .attr("opacity", function(d, j) {
        return j != i ? 0.6 : 1;
    })})

    .on("mousemove", function(d, i) {
      var datearray = [];
      var mousex = d3.mouse(this);
      mousex = mousex[0];
      var invertedx = x.invert(mousex);
      //invertedx = invertedx.getFullYear();
      var selected = (d.values);
      for (var k = 0; k < selected.length; k++) {
        datearray[k] = selected[k].date; //.getFullYear();
        // datearray[k] = datearray[k].getMonth() + datearray[k].getDate();
      }

      var mousedate = datearray.indexOf(Math.round(invertedx));
      pro = 'undefined'; yr = 'undefined';
      if (mousedate != -1) {
        pro = d.values[mousedate].value;
        yr = d.values[mousedate].year;
      }
      var mm = d3.mouse(this);
      var mx = mm[0] + 20;
      var my = mm[1] + 0;
      d3.select(this)
        .classed("hover", true)
        .attr("stroke", "#fff")
        .attr("stroke-width", "2px"), 
      tooltip.style("left",mx+"px");
      tooltip.style("top",my+"px");
      /*for(var i in _STREAMGRAPH.stems) {
        if (d.key == _STREAMGRAPH.stems[i][0]) {
          var keyword1 = _STREAMGRAPH.stems[i][1];
        }
      } */
      tooltip.html( "<div style='text-align:left;color:#000;background-color:#fff;border-radius:3px;padding:10px;20px;font-size:0.9em;width:250px'>Keyword:<b> " + d.key.capitalizeFirstLetter() + "</b><br/>Year: " + yr+ "<br/>Count: " + pro + "</div>" ).style("visibility", "visible");
      displayDetails(d.key, yr);
      
    })
  //   .on("mouseout", function(d, i) {
  //    svg.selectAll(".layer")
  //     .transition()
  //     .duration(250)
  //     .attr("opacity", "1");
  //     // .attr("padding-top", "30px");
  //     d3.select(this)
  //     .classed("hover", false)
  //     .attr("stroke-width", "0px"), tooltip.html( "<p>" + d.key + "<br>" + pro + "</p>" ).style("visibility", "hidden");
  // })
    
  /*var vertical = d3.select(".chart")
        .append("div")
        .attr("class", "remove")
        .style("position", "absolute")
        .style("z-index", "19")
        .style("width", "1px")
        .style("height", "380px")
        .style("top", "10px")
        .style("bottom", "30px")
        .style("left", "0px")
        .style("background", "#fff"); */

  d3.select("#sg_chart")
      .on("mousemove", function(){  
         var mousex = d3.mouse(this);
         mousex = mousex[0] + 5})
         // vertical.style("left", mousex + "px" )})
      .on("mouseover", function(){  
         var mousex = d3.mouse(this);
         mousex = mousex[0] + 5});
         // vertical.style("left", mousex + "px")});
});

}

function backFillData(data, data_years, width) {

  var unique = data_years.filter( onlyUnique ); 
  var firstdate = String(Math.min.apply(null, unique)-1)  ;
  unique.push(firstdate);
  unique.push(String(new Date().getFullYear()+1));
  unique.sort();
  var outputdata = [];
  
  for(var prop in data) {
    for(var i=0;i<unique.length;i++) {
        if(data[prop][unique[i]])
            outputdata.push({'key':prop,'year':unique[i],'date':i,'value':data[prop][unique[i]]});
        else
            outputdata.push({'key':prop,'year':unique[i],'date':i,'value':0});
    }
  }
  var content = "";
  var newwidth = width/(unique.length-3)-5;
  for(var i=0;i<unique.length;i++) {
    content += "<div style='position:absolute;margin-top:5px;text-align:left;float:left;color:#666;left:"+(newwidth*i)+"px'>"+unique[i]+"</div>";
  }
  $('#timewrapper').html(content);

  return outputdata;
}
function onlyUnique(value, index, self) { 
    return self.indexOf(value) === index;
}




function loadDetails(details) {
  $.ajax({
      type: "GET",
      url: details,
      dataType: "json",
      success: function(data) {
        var x = data.results.bindings;
        
        for(var i=0;i<x.length;i++) {
            // Authors
            var a = x[i].authorname.value.toLowerCase();
            if (authors[x[i].key.value]) {
                if (authors[x[i].key.value][a]) {
                  authors[x[i].key.value][a] += 1;
                } else {
                  authors[x[i].key.value][a] = 1;
                }

            } else {
              authors[x[i].key.value] = {};
              authors[x[i].key.value][a] = 1;
            }
            // Paper Titles
            a = x[i].title.value;
            if (title[x[i].key.value]) {
                if (title[x[i].key.value][a]) {
                  title[x[i].key.value][a] += 1;
                } else {
                  title[x[i].key.value][a] = 1;
                }

            } else {
              title[x[i].key.value] = {};
              title[x[i].key.value][a] = 1;
            }
        }

      }
   });
}

function displayDetails(key, date) {
  var yearscontent = "";
  for(var prop in _STREAMGRAPH.data.years) {
    if (key == prop) {
      for(var p in _STREAMGRAPH.data.years[prop]) {
        yearscontent += "<div style='text-align:left;padding:3px 10px;margin-top:1px;width:95%;border-radius:3px;background-color:white;'><span style='font-weight:bold;color:#fb0707'>"+p+": </span><span style='color:black'> " + _STREAMGRAPH.data.years[prop][p] + "</span></div>";
      }
    }
  }
  $('#wrapperYearsContent').html(yearscontent);

  var authorcontent = "";
  // console.log(_STREAMGRAPH.data.authors);
  for(var prop in _STREAMGRAPH.data.authors) {
    if (key == prop) {
      for(var p in _STREAMGRAPH.data.authors[prop]) {
  if (date == p) {
    for(var i=0;i<_STREAMGRAPH.data.authors[prop][p].length;i++) {
      authorcontent += "<div style='text-align:left;padding:3px 10px;margin-top:1px;width:95%;border-radius:3px;background-color:white;'><span style='font-weight:bold;color:#fb0707'><a target='_blank' href='"+_STREAMGRAPH.data.authors[prop][p][i][2].replace("lod.","")+"'>"+_STREAMGRAPH.data.authors[prop][p][i][0].capitalizeFirstLetter()+"</a>: </span><span style='color:black'> " + _STREAMGRAPH.data.authors[prop][p][i][1] + "</span></div>";
          }
  }
      }
    }
  }
  $('.authoryear').html("("+date+")");
  $('#wrapperAuthorsContent').html(authorcontent);

  var titlecontent = "";
  for(var prop in _STREAMGRAPH.data.titles) {
    if (key == prop) {
      for(var p in _STREAMGRAPH.data.titles[prop]) {
  if (date == p) {
    for(var i=0;i<_STREAMGRAPH.data.titles[prop][p].length;i++) {
      // console.log(_STREAMGRAPH.data.titles[prop][p]);
      titlecontent += "<div style='text-align:left;padding:3px 10px;margin-top:1px;width:95%;border-radius:3px;background-color:white;'><a target='_blank' href='"+_STREAMGRAPH.data.titles[prop][p][i][1].replace("lod.", "")+"'>"+_STREAMGRAPH.data.titles[prop][p][i][0]+"</a></div>";
          }
  }
      }
    }
  }
  $('#wrapperPaperContent').html(titlecontent);
  var max = 0;
  for(var prop in _STREAMGRAPH.data.countries) {
    // console.log(_STREAMGRAPH.data.countries);
    if (key == prop) {

      for(var p in _STREAMGRAPH.data.countries[prop]) {
        if (date == p) {
          var x = {};
          for(var j=0;j<countries.length;j++) {
            x[countries[j].iso3] = "#333";
            for(var i=0;i<_STREAMGRAPH.data.countries[prop][p].length;i++) {
               if(parseInt(_STREAMGRAPH.data.countries[prop][p][i][1]) > max) 
                  max = parseInt(_STREAMGRAPH.data.countries[prop][p][i][1]);
            } 
            for(var i=0;i<_STREAMGRAPH.data.countries[prop][p].length;i++) { 
              if(countries[j].countryName == _STREAMGRAPH.data.countries[prop][p][i][0]) {
                var c = parseInt(_STREAMGRAPH.data.countries[prop][p][i][1]) / max;
                if (c > 0.8)
                  x[countries[j].iso3] = "rgb(165,15,21)";
                else if (c > 0.6)
                  x[countries[j].iso3] = "rgb(222,45,38)";
                else if (c > 0.4)
                  x[countries[j].iso3] = "rgb(251,106,74)";
                else if (c > 0.2)
                  x[countries[j].iso3] = "rgb(252,174,145)";
                else if (c > 0)
                  x[countries[j].iso3] = "rgb(254,229,217)"; 
                // ['rgb(254,229,217)','rgb(252,174,145)','rgb(251,106,74)','rgb(222,45,38)','rgb(165,15,21)'] 
              }
            }
          }
          _STREAMGRAPH.map.updateChoropleth(x);
          break;
        }
        
      }
      break;
    }
    
   }
}

// shuffle the colors
function shuffle(array) {
  var currentIndex = array.length, temporaryValue, randomIndex ;

  // While there remain elements to shuffle...
  while (0 !== currentIndex) {

    // Pick a remaining element...
    randomIndex = Math.floor(Math.random() * currentIndex);
    currentIndex -= 1;

    // And swap it with the current element.
    temporaryValue = array[currentIndex];
    array[currentIndex] = array[randomIndex];
    array[randomIndex] = temporaryValue;
  }

  return array;
}

function responsive(){
   // _STREAMGRAPH.map.resize();
  var chart = $("#streamgraph"),
    aspect = chart.width() / chart.height(),
    container = chart.parent();
$(window).on("resize", function() {
    // console.log(window.innerWidth);
    var targetWidth = container.width();
    chart.attr("width", targetWidth);
    // chart.attr("height", Math.round(targetWidth / aspect));
}).trigger("resize");
}
