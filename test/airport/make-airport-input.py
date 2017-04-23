
from geopy.distance import distance
import csv


DAT_AIRPORTS = './data/airports.dat'
DAT_ROUTES = './data/routes.dat'
INPUT = './data/input.txt'


class Airport(object):
    def __init__(self, id: int, name: str, lat: float, lng: float):
        self.id = id
        self.name = name
        self.lat = lat
        self.lng = lng
        self.adj = []

    def __str__(self):
        line = str(self.id)
        for adjacent in self.adj:
            line += ' ' + str(adjacent[0]) + ' ' + str(adjacent[1])
        return line


def distance_in_km(a: Airport, b: Airport) -> float:
    """
        Estimates the exact distance between two airports in km
    """
    a_loc = (a.lat, a.lng)
    b_loc = (b.lat, b.lng)
    return distance(a_loc, b_loc).kilometers


def load_airport_data() -> tuple:
    airport_lst = []
    airport_map = {}

    with open(DAT_AIRPORTS) as csv_file:
        reader = csv.reader(csv_file)
        for row in reader:
            ap = Airport(
                id=int(row[0]),
                name=row[1],
                lat=float(row[6]),
                lng=float(row[7])
            )
            airport_lst.append(ap)
            airport_map[ap.id] = ap

    return airport_lst, airport_map


def load_route_data(airport_map: dict) -> None:

    with open(DAT_ROUTES) as csv_file:
        reader = csv.reader(csv_file)
        for row in reader:
            try:
                ap_src_id = int(row[3])
                ap_dst_id = int(row[5])
                ap_src = airport_map[ap_src_id]
                ap_dst = airport_map[ap_dst_id]
            except ValueError:
                continue
            except KeyError:
                continue

            weight = distance_in_km(ap_src, ap_dst)
            ap_src.adj.append((ap_dst.id, weight))


def run():
    # Load in airport data
    airport_lst, airport_map = load_airport_data()

    # Load in route data
    load_route_data(airport_map)

    # Print in correct input format
    print(len(airport_lst))
    for ap in airport_lst:
        print(ap)

run()
