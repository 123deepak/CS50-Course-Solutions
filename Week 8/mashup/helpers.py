import feedparser
import urllib.parse

def lookup(geo):
    ""
"Looks up articles for geo."
""
if geo in lookup.cache:
    return lookup.cache[geo]
feed = feedparser.parse("http://news.google.com/news?geo={}&output=rss".format(urllib.parse.quote(geo, safe = "")))
if not feed["items"]:
    feed = feedparser.parse("http://www.theonion.com/feeds/rss")
lookup.cache[geo] = [{
        "link": item["link"],
        "title": item["title"]
    }
    for item in feed["items"]
]
return lookup.cache[geo]
lookup.cache = {}