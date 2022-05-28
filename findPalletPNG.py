import sys
from bs4 import BeautifulSoup
import requests

BASE_URL = "http://soliton.vm.bytemark.co.uk/pub/cpt-city/"

def map_internal_link_lambda(base):
    return (lambda link: base + link['href'][0:-10] if link['href'].endswith('index.html') else base + link['href'])

def filter_internal_link(link):
    if (link['href'].startswith('http') or link['href'].startswith('..')):
        return False
    if (link['href'][-1] == '/'):
        return True
    return link['href'].endswith('/index.html')
    """
    return list(map(lambda a: base + a['href'][0:-10], filter(lambda a: not (a['href'].startswith('http') or a['href'].startswith('..') or a['href'].endswith('.index.html') or a['href'].endswith('COPYING.xml') or a['href'].endswith('copying.html')), soup.find_all('a', href=True))))
    """


def get_internal_links(soup, base):
    return map(map_internal_link_lambda(base), filter(filter_internal_link, soup.find_all('a', href=True)))

def get_img_links(soup, keyword):
    return map(lambda img: img['src'], filter(lambda img: img['src'].endswith(keyword + '.png'), soup.find_all('img')))

def get_all_img_links(soup):
    return map(lambda img: img['src'], soup.find_all('img'))

if __name__ == "__main__":
    # base_page = requests.get(BASE_URL + "/index.html")
    # soup = BeautifulSoup(base_page.content, 'html.parser')
    all_images = []
    potential_images = []
    visited = {""}
    to_visit = {""}
    do_all = len(sys.argv) == 1
    if do_all:
        print("DOING THEM ALL")
    else:
        png_name = sys.argv[1]


    while to_visit:
        a = to_visit.pop()
        print("Visiting " + a)
        visited.add(a)
        s = BeautifulSoup(requests.get(BASE_URL + a + "index.html").text, 'html.parser')
        u = filter(lambda a: a not in visited, get_internal_links(s, a))
        # print("NEW LINKS: " + str(list(u)))
        to_visit.update(u)
        print(len(to_visit))

        if do_all:
            for link in get_all_img_links(s):
                all_images.append(BASE_URL + a + link)
        else:
            for img in get_img_links(s, png_name):
                print("POTENTIAL IMAGE: " + img)
                potential_images.append(img)

    if do_all:
        with open('img_links.txt', 'w') as f:
            for item in all_images:
                f.write("%s\n" % item)
    print(potential_images)
        


