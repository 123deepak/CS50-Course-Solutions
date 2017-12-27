var map;

var markers = [];
var info = new google.maps.InfoWindow();
$(function() {

    var styles = [

        {
            featureType: "all",
            elementType: "labels",
            stylers: [{
                visibility: "off"
            }]
        },
        {
            featureType: "road",
            elementType: "geometry",
            stylers: [{
                visibility: "off"
            }]
        }

    ];
    var options = {
        center: {
            lat: 42.3770,
            lng: -71.1256
        }, // Cambridge
        disableDefaultUI: true,
        mapTypeId: google.maps.MapTypeId.ROADMAP,
        maxZoom: 14,
        panControl: true,
        styles: styles,
        zoom: 13,
        zoomControl: true
    };
    var canvas = $("#map-canvas").get(0);
    map = new google.maps.Map(canvas, options);
    google.maps.event.addListenerOnce(map, "idle", configure);

});

/**
 * Adds marker for place to map.
 */
function addMarker(place) {
    var myLatLng = new google.maps.LatLng(place["latitude"], place["longitude"]);

    var image = "http://maps.google.com/mapfiles/kml/pal2/icon31.png";
    var marker = new google.maps.Marker({
        position: myLatLng,
        map: map,
        title: place["place_name"] + ", " + place["admin_name1"],
        label: place["place_name"] + ", " + place["admin_name1"],
        icon: image
    });
    $.getJSON(Flask.url_for("articles"), {
        geo: place.postal_code
    }, function(articles) {
        if (!$.isEmptyObject(articles)) {
            var articlesContent = "<ul>";
            for (var i = 0; i < articles.length; i++) {
                articlesContent += "<li><a target='_NEW' href='" + articles[i].link +
                    "'>" + articles[i].title + "</a></li>";
            }
        }
        articlesContent += "</ul>";
        google.maps.event.addListener(marker, 'click', function() {
            showInfo(marker, articlesContent);
        });
    });
    markers.push(marker);
}

/**
 * Configures application.
 */
function configure() {
    google.maps.event.addListener(map, "dragend", function() {
        if (!info.getMap || !info.getMap()) {
            update();
        }
    });
    google.maps.event.addListener(map, "zoom_changed", function() {
        update();
    });
    $("#q").typeahead({
        highlight: false,
        minLength: 1
    }, {
        display: function(suggestion) {
            return null;
        },
        limit: 10,
        source: search,
        templates: {
            suggestion: Handlebars.compile(
                "<div>" +
                "{{ place_name }}, {{ admin_name1 }}, {{ postal_code }}" +
                "</div>"
            )
        }
    });
    $("#q").on("typeahead:selected", function(eventObject, suggestion, name) {
        map.setCenter({
            lat: parseFloat(suggestion.latitude),
            lng: parseFloat(suggestion.longitude)
        });
        update();
    });
    $("#q").focus(function(eventData) {
        info.close();
    });
    document.addEventListener("contextmenu", function(event) {
        event.returnValue = true;
        event.stopPropagation && event.stopPropagation();
        event.cancelBubble && event.cancelBubble();
    }, true);
    update();
    $("#q").focus();
}

/**
 * Removes markers from map.
 */
function removeMarkers() {
    for (var k1 = 0, n = markers.length; k1 < n; k1++) {
        markers[k1].setMap(null);
    }
}

/**
 * Searches database for typeahead's suggestions.
 */
function search(query, syncResults, asyncResults) {
    var parameters = {
        q: query
    };
    $.getJSON(Flask.url_for("search"), parameters)
        .done(function(data, textStatus, jqXHR) {
            asyncResults(data);
        })
        .fail(function(jqXHR, textStatus, errorThrown) {
            console.log(errorThrown.toString());
            asyncResults([]);
        });
}
/**
 * Shows info window at marker with content.
 */
function showInfo(marker, content) {
    var div = "<div id='info'>";
    if (typeof(content) == "undefined") {
        div += "<img alt='loading' src='/static/ajax-loader.gif'/>";
    } else {
        div += content;
    }
    div += "</div>";
    info.setContent(div);
    info.open(map, marker);
}

/**
 * Updates UI's markers.
 */
function update() {
    var bounds = map.getBounds();
    var ne = bounds.getNorthEast();
    var sw = bounds.getSouthWest();

    var parameters = {
        ne: ne.lat() + "," + ne.lng(),
        q: $("#q").val(),
        sw: sw.lat() + "," + sw.lng()
    };
    $.getJSON(Flask.url_for("update"), parameters)
        .done(function(data, textStatus, jqXHR) {
            removeMarkers();
            for (var m1 = 0; m1 < data.length; m1++) {
                addMarker(data[m1]);
            }
        })
        .fail(function(jqXHR, textStatus, errorThrown) {

            console.log(errorThrown.toString());
        });
};