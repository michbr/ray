#include "renderer.h"

#include "dragonmath.h"
#include "MatMath.h"
#include <cmath>

//#include <iostream>

using namespace std;

int standardize(int a) {
	if (a > 255) {
		a = 255;
	}
	return a;
}

Renderer::Renderer(Camera * c) {
	cam = c;
}

void Renderer::set_frame(Wireframe * new_frame) {
	frame = new_frame;
	vector<vector<int>*> * bitmap = new  vector<vector<int>* >();
	vector<vector<double>*> * z_map = new  vector<vector<double>* >();
	for (int i = 0; i < abs(frame->get_miny()) + frame->get_maxy(); i++) {
		vector<int> * row = new vector<int>();
		//vector<int> * rowz = new vector<int>();
		for (int j = 0; j < 3 * (abs(frame->get_minx()) + frame->get_maxx()); j++) {
			row->push_back(0);
			//rowz->push_back(0);
		}
		bitmap->push_back(row);
		//z_map->push_back(rowz);
	}

	for (int i = 0; i < abs(frame->get_miny()) + frame->get_maxy(); i++) {
		vector<double> * row = new vector<double>();
		//vector<int> * rowz = new vector<int>();
		for (int j = 0; j < (abs(frame->get_minx()) + frame->get_maxx()); j++) {
			row->push_back(0);
			//rowz->push_back(0);
		}
		z_map->push_back(row);
		//z_map->push_back(rowz);
	}
	image = bitmap;
	z_buffer = z_map;
	has_frame = true;
}

void Renderer::fill(int x, int y, int r, int g, int b) {
	//if (((*(*z_buffer)[y+abs(frames[0].get_miny())])[(x + abs(frames[0].get_minx()))] == 0) ^ (d < (*(*z_buffer)[y+abs(frames[0].get_miny())])[(x + abs(frames[0].get_minx()))])) {
	//(*(*z_buffer)[y+abs(frames[0].get_miny())])[(x + abs(frames[0].get_minx()))] = d;
	(*(*image)[y + abs(frame->get_miny())])[3 * (x + abs(frame->get_minx()))] = r;
	(*(*image)[y + abs(frame->get_miny())])[3 * (x + abs(frame->get_minx())) + 1] = g;
	(*(*image)[y + abs(frame->get_miny())])[3 * (x + abs(frame->get_minx())) + 2] = b;
	//}
}

vector<int> * Renderer::find_closest_face(std::vector<double> * source, std::vector<double> * destination, const std::vector<Face *> & faces, const vector<Elipse *> & elipses, const vector<Light *> & lights, int depth, double * distance, bool * found) {
	// cout << "find face" << endl;
	double d;
	*found = false;

	Face * face;
	vector<double> * point;

	double current_distance;
	double min_distance = 0;
	double T;
	for (int i = 0; i < faces.size(); i++) {
		
		vector<double> * temp = faces[i]->intersect(source, destination, &T);
		if (faces[i]->is_inside(temp)) {
			if (T > 0) {
				vector<double> * sbt = subtract(temp, source);
				current_distance = magnitude(sbt);
				delete(sbt);
				// cout << "found face" << endl;
				if (!(*found)) {
					min_distance = current_distance;
					face = faces[i];

					point = temp;
					*found = true;
				}
				else if (min_distance > current_distance) {
					min_distance = current_distance;
					face = faces[i];
					//point->clear();
					//point->~vector();
					delete(point);
					point = temp;
				}
			}
			else {
				delete(temp);
			}
		}
		else {
			delete(temp);
		}
	}
	*distance = min_distance;
	if (*found) {
		return color_face_pixel(source, point, face, faces, elipses, lights, depth);
	}

}

vector<int> * Renderer::find_closest_elipse(std::vector<double> * source, std::vector<double> * destination, const std::vector<Face *> & faces, const std::vector<Elipse *> & elipses, const vector<Light *> & lights, int depth, double * distance, bool * found) {
	// cout << "starting" << endl;
	double d;
	*found = false;

	Elipse * elipse;
	vector<double> * point;

	double current_distance;
	*distance = 0;
	//double min_distance = magnitude(subtract(destination, source));
	double min_distance = 0;
	for (int i = 0; i < elipses.size(); i++) {
		vector<double> * temp = elipses[i]->intersect(source, destination);
		if (elipses[i]->is_inside(temp)) {
			current_distance = magnitude(subtract(temp, source));
			//cout << "testing" << endl;
			if (!elipses[i]->is_inside(source)) {
				//cout << "got inside" << endl;
				if (!(*found)) {
					min_distance = current_distance;
					elipse = elipses[i];
					point = temp;
					*found = true;
				}
				else if (min_distance > current_distance) {
					min_distance = current_distance;
					elipse = elipses[i];
					point = temp;
				}
			}
			//  cout << "on the other side" << endl;
		}
		//cout << "about to loop" << endl;
	}
	// cout << "after the loop" << endl;
	*distance = min_distance;
	//cout << "distance" << endl;
	if (*found) {
		//cout << "returning" << endl;
		return color_elipse_pixel(source, point, elipse, faces, elipses, lights, depth);
	}
}

vector<int> * Renderer::color_face_pixel(std::vector<double> * source, std::vector<double> * destination, Face * face, const vector<Face *> &faces, const vector<Elipse *> &elipses, const std::vector<Light * > & lights, int depth) {
	//cout << "got here" << endl;   
	vector<int> * final = new vector<int>();
	int r, g, b;
	r = g = b = 0;
	//cout << "got here" << endl;
	vector<int> * ambient = face->get_material()->color_ambient(lights[0]->get_color());
	// cout << "got here" << endl;
	r += (*ambient)[0];
	g += (*ambient)[1];
	b += (*ambient)[2];
	delete(ambient);

	/*
	*  Calculate bounce lighting
	*
	*
	*/
	if (depth > 1) {
		const vector<double> * normal = face->get_normal();
		vector<double> * L = subtract(source, destination);
		vector<double> * scl = scale(normal, 2 * dot_product(L, normal));
		vector<double> * sbt = subtract(scl, L);
		vector<double> * new_dest = add(sbt, destination);
		delete(sbt);
		delete(scl);
		//double dot = dot_product(subtract(source, destination), normal);
		//vector<double> * p = scale(normal, dot);
		//vector<double> * q = add(destination, p);
		//vector<double> * mover = subtract(q, source);
		//vector<double> * new_dest = add(q, mover);

		//normal->~vector();
		//p->~vector();
		//mover->~vector();

		vector<int> * rfl_color;

		Face * new_face;
		Elipse * new_elipse;


		double f_dist;
		//double e_dist;

		bool found_face = false;
		bool found_elipse = false;
		//cout << "color face" << endl;
		vector<int> * reflective = find_closest_face(destination, new_dest, faces, elipses, lights, depth - 1, &f_dist, &found_face);
	//	vector<int> * sphere = find_closest_elipse(destination, new_dest, faces, elipses, lights, depth - 1, &e_dist, &found_elipse);
		//cout << "after find" << endl;

		vector<double> * dest;
		Light * reflection;
		//string mat;
		/*if (found_face && found_elipse) {
			//  cout << "found both" << endl;
			if (f_dist < e_dist) {
				vector<double> * sbt = subtract(new_dest, destination);
				vector<double> * norm = normalize(sbt);
				dest = scale(norm, f_dist);
				reflection = new Light((*dest)[0], (*dest)[1], (*dest)[2], 1, (*reflective)[0], (*reflective)[1], (*reflective)[2]);
				sbt->clear();
				sbt->~vector();
				norm->clear();
				norm->~vector();
			}
			else {
				vector<double> * sbt = subtract(new_dest, destination);
				vector<double> * norm = normalize(sbt);
				dest = scale(norm, e_dist);
				reflection = new Light((*dest)[0], (*dest)[1], (*dest)[2], 1, (*sphere)[0], (*sphere)[1], (*sphere)[2]);
				sbt->clear();
				sbt->~vector();
				norm->clear();
				norm->~vector();
			}*/

		//}
		//else
		if (found_face) {
			//  cout << found_face << endl;
			vector<double> * sbt = subtract(new_dest, destination);
			vector<double> * norm = normalize(sbt);
			dest = scale(norm, f_dist);
			reflection = new Light((*dest)[0], (*dest)[1], (*dest)[2], 1, (*reflective)[0], (*reflective)[1], (*reflective)[2]);
			delete(sbt);
			delete(norm);
		}
		/*else if (found_elipse){
			vector<double> * sbt = subtract(new_dest, destination);
			vector<double> * norm = normalize(sbt);
			dest = scale(norm, e_dist);
			reflection = new Light((*dest)[0], (*dest)[1], (*dest)[2], 1, (*sphere)[0], (*sphere)[1], (*sphere)[2]);
			sbt->clear();
			sbt->~vector();
			norm->clear();
			norm->~vector();
		}*/
		//cout << "got light color" << endl;
		//reflective->~vector();
		//sphere->~vector();

		if (found_face) {// || found_elipse) {
			vector<int> * reflection_color = face->get_material()->color_specular(reflection->get_color(), 1);
			r += (*reflection_color)[0];
			g += (*reflection_color)[1];
			b += (*reflection_color)[2];
			delete(reflection_color);
		}
		delete(new_dest);
		delete(reflection);
		delete(dest);
		delete(reflective);
	}

	/*
	*	Calculate specular and diffuse lighting
	*
	*/
	//cout << lights.size() << endl;
	for (int j = 1; j < lights.size(); j++) {
		if (!lights[j]->is_blocked(destination, faces, elipses)) {
			vector<double> * sbt = subtract(lights[j]->get_center(), destination);
			vector<double> * norm = normalize(sbt);
			double c = dot_product(face->get_normal(), norm); //switched these
			delete(sbt);
			delete(norm);

			sbt = subtract(source, destination);
			norm = normalize(sbt);
			double awesome = dot_product(face->get_normal(), norm);
			delete(sbt);
			delete(norm);
			//  cout << "into loop" << endl;
			if (((c < 0) && (awesome < 0)) || ((c > 0) && (awesome > 0))) {
				// cout << "past c" << endl;
				vector<int> * color = face->color_diffuse(destination, lights[j]->get_color(), c);
				r += (*color)[0];
				g += (*color)[1];
				b += (*color)[2];
				delete(color);
			}
			sbt = subtract(lights[j]->get_center(), destination);
			vector<double> * L = normalize(sbt);
			delete(sbt);

			const vector<double> * N = face->get_normal();

			sbt = subtract(source, destination);
			vector<double> * V = normalize(sbt);
			delete(sbt);

			vector<double> * scl = scale(N, 2 * dot_product(L, N));
			sbt = subtract(scl, L);
			double dot = dot_product(V, sbt);
			delete(sbt);
			delete(scl);

			if (dot > 0) {
				vector<int> * specular = face->get_material()->color_specular(lights[j]->get_color(), dot);
				r += (*specular)[0];
				g += (*specular)[1];
				b += (*specular)[2];
				delete(specular);
			}
			delete(L);
			//N->~vector();
			delete(V);

		}
	}
//	destination->clear();
//	destination->~vector();
	delete(destination);
	
	final->push_back(r);
	final->push_back(g);
	final->push_back(b);
	return final;

}

vector<int> * Renderer::color_elipse_pixel(std::vector<double> * source, vector<double> * destination, const Elipse * elipse, const vector<Face *> &faces, const vector<Elipse *> &elipses, const std::vector<Light * > & lights, int depth) {
	vector<int> * final = new vector<int>();
	int r, g, b;
	r = g = b = 0;
	vector<int> * ambient = elipse->get_material()->color_ambient(lights[0]->get_color());
	r += (*ambient)[0];
	g += (*ambient)[1];
	b += (*ambient)[2];
	delete(ambient);


	if (depth > 1) {
		//const vector<double> * normal = elipse->get_normal(destination);
		//double dot = dot_product(subtract(source, destination), normal);
		//vector<double> * p = scale(normal, dot);
		//vector<double> * q = add(destination, p);
		//vector<double> * mover = subtract(q, source);
		//vector<double> * new_dest = add(q, mover);
		//vector<double> * mover = subtract(q, source);
		//vector<double> * new_dest = add(source, scale(mover, 2));
		//double one = (*new_dest)[0];
		//double two = (*new_dest)[1];
		//double three = (*new_dest)[2];
		//cout << one << " " << two <<  " " << three << endl;
		//vector<double> * L = normalize(subtract(lights[j]->get_center(), destination));
		//vector<double> * N = normalize(normal);
		//vector<double> * view = normalize(subtract(source, destination));
		//double test = (*view)[0];
		//new_dest = subtract(scale(N, 2*dot_product(view, N)), view);
		//cout << "depth" << depth << endl;
		vector<double> * normal = elipse->get_normal(destination);
		//cout << "source: " << (*source)[0] << " " << (*source)[1]  << " " << (*source)[2]  << endl;
		//cout << "dest: " << (*destination)[0] << " " << (*destination)[1]  << " " << (*destination)[2]  << endl;
		//cout << "L: " << (*L)[0] << " " << (*L)[1]  << " " << (*L)[2]  << endl;

		//vector<double> * N = normalize(normal);
		//vector<double> * V = normalize(subtract(source, destination));
		//cout << "L: " << (*L)[0] << " " << (*L)[1]  << " " << (*L)[2]  << endl;
		//cout << "N: " << (*N)[0] << " " << (*N)[1]  << " " << (*N)[2]  << endl;
		vector<double> * L = subtract(source, destination);
		vector<double> * new_dest = add(subtract(scale(normal, 2 * dot_product(L, normal)), L), destination);
		//if (dot_product(normalize(subtract(source, destination)), normalize(subtract(new_dest, destination))) < 0) {
		// cout << dot_product(subtract(source, destination), subtract(new_dest, destination)) << endl;

		//double one = (*test)[0];
		//double two = (*test)[1];
		//double three = (*test)[2];
		//cout << one << " " << two <<  " " << three << endl;
		//vector<double> * new_dest = new vector<double>();
		//new_dest->push_back((*test)[0]);
		//new_dest->push_back((*test)[1]);
		//new_dest->push_back((*test)[2]);
		//normal->~vector();
		//p->~vector();
		//mover->~vector();

		vector<int> * rfl_color;

		Face * new_face;
		Elipse * new_elipse;


		double f_dist;
		double e_dist;

		bool found_face = false;
		bool found_elipse = false;

		vector<int> * reflective = find_closest_face(destination, new_dest, faces, elipses, lights, depth - 1, &f_dist, &found_face);
		//cout << "new_dest: " << (*new_dest)[0] << " " << (*new_dest)[1]  << " " << (*new_dest)[2]  << endl;
		//vector<int> * sphere = find_closest_elipse(new_dest, destination, faces, elipses, lights, materials, depth -1, &e_dist, &found_elipse);
		//cout << "depth " << depth << endl; 
		vector<int> * sphere = find_closest_elipse(destination, new_dest, faces, elipses, lights, depth - 1, &e_dist, &found_elipse);

		vector<double> * dest;
		Light * reflection;
		//string mat;
		if (found_face && found_elipse) {

			if (f_dist < e_dist) {
				dest = scale(normalize(subtract(new_dest, destination)), f_dist);
				reflection = new Light((*dest)[0], (*dest)[1], (*dest)[2], 1, (*reflective)[0], (*reflective)[1], (*reflective)[2]);
			}
			else {
				dest = scale(normalize(subtract(new_dest, destination)), e_dist);
				reflection = new Light((*dest)[0], (*dest)[1], (*dest)[2], 1, (*sphere)[0], (*sphere)[1], (*sphere)[2]);
			}

		}
		else if (found_face) {
			dest = scale(normalize(subtract(new_dest, destination)), f_dist);
			reflection = new Light((*dest)[0], (*dest)[1], (*dest)[2], 1, (*reflective)[0], (*reflective)[1], (*reflective)[2]);
		}
		else if (found_elipse) {
			dest = scale(normalize(subtract(new_dest, destination)), e_dist);
			double i = (*dest)[0];
			double j = (*dest)[1];
			double k = (*dest)[2];
			//double l = (*dest)[0];
			int r1 = (*sphere)[0];
			int g1 = (*sphere)[1];
			int b1 = (*sphere)[2];
			// cout << i << " " << j << " " << k << endl;
			//cout << "-----------------------" << endl;
			reflection = new Light((*dest)[0], (*dest)[1], (*dest)[2], 1, (*sphere)[0], (*sphere)[1], (*sphere)[2]);
			// reflection = new Light(i, j, k, 1, r1, g1, b1);
		}

		//reflective->~vector();
		//sphere->~vector();
		if (found_face || found_elipse) {
			vector<int> * reflection_color = elipse->get_material()->color_reflection(reflection->get_color());
			r += (*reflection_color)[0];
			g += (*reflection_color)[1];
			b += (*reflection_color)[2];
			reflection_color->~vector();
		}
		//}
	}


	for (int j = 1; j < lights.size(); j++) {
		//bool blocked = false;
		if (!lights[j]->is_blocked(destination, faces, elipses)) {
			double c = dot_product(normalize(elipse->get_normal(destination)), normalize(subtract(lights[j]->get_center(), destination)));
			if (c > 0) {
				vector<int> * color = elipse->get_material()->color_diffuse(lights[j]->get_color(), c);
				r += (*color)[0];
				g += (*color)[1];
				b += (*color)[2];
				color->~vector();
			}

			vector<double> * L = normalize(subtract(lights[j]->get_center(), destination));
			vector<double> * N = normalize(elipse->get_normal(destination));
			vector<double> * V = normalize(subtract(source, destination));
			double dot = dot_product(V, subtract(scale(N, 2 * dot_product(L, N)), L));
			if (dot > 0) {
				vector<int> * specular = elipse->get_material()->color_specular(lights[j]->get_color(), dot);
				r += (*specular)[0];
				g += (*specular)[1];
				b += (*specular)[2];
				specular->~vector();
			}
			L->~vector();
			N->~vector();
			V->~vector();
		}
	}

	double tr = elipse->get_material()->get_tr();
	if (tr > 0) {
		vector<double> * ray = normalize(subtract(source, destination));
		vector<double> * e_normal = elipse->get_normal(destination);
		double n_dot_r = dot_product(e_normal, ray);
		if (n_dot_r > 0) {
			double alpha = 1 / 1.5;
			double radical = 1 - (alpha*alpha) + ((alpha*alpha)*(n_dot_r*n_dot_r));
			double beta = (-alpha)*n_dot_r - sqrt(radical);
			if (!(radical < 0)){
				//cout << "scream!!!" << endl;

				vector<double> * T = add(scale(ray, alpha), scale(e_normal, beta));
				//}

				//vector<double> * direction = T;

				//vector<double> * line = subtract(elipse->get_center(), source);// = new vector<double>();

				//	double v = dot_product(line, normalize(direction));
				//double c = magnitude(line);
				//double b = c*c - v*v;
				//double r = elipse->get_radius();
				//double d = sqrt(r*r - (c*c - v*v));

				alpha = 1.5;
				vector<double> * exit_point = elipse->intersect(add(scale(T, 2), destination), add(scale(T, 1.5), destination));//add(scale(normalize(T), 2*d), destination);
				if (!elipse->is_inside(exit_point)) {
					//cerr << "Point is not inside!" << endl;
					exit(1);
				}
				vector<double> * exit_normal = elipse->get_normal(exit_point);
				double n_dot_t = dot_product(exit_normal, normalize(T));


				radical = 1 - (alpha*alpha) + ((alpha*alpha)*(n_dot_t*n_dot_t));
				beta = (-alpha)*n_dot_t - sqrt(radical);
				//if (radical >= 0){
				vector<double> * T1 = add(scale(T, alpha), scale(exit_normal, beta));

				//Get the color!
				vector<int> * f_color;
				vector<int> * e_color;


				bool found_face = false;
				bool found_elipse = false;

				double f_dist;
				double e_dist;

				//cout << "got here" << endl;
				f_color = find_closest_face(exit_point, add(T1, exit_point), faces, elipses, lights, depth - 1, &f_dist, &found_face);
				e_color = find_closest_elipse(exit_point, add(T1, exit_point), faces, elipses, lights, depth - 1, &e_dist, &found_elipse);

				vector<int> * color;
				if (found_face && found_elipse) {
					if (f_dist < e_dist) {
						color = f_color;
					}
					else {
						color = e_color;
					}

				}
				else if (found_face) {
					color = f_color;
				}
				else {
					color = e_color;
				}
				if (found_face || found_elipse) {
					vector<double> * L1 = new vector<double>();
					L1->push_back(r);
					L1->push_back(g);
					L1->push_back(b);
					vector<double> * L2 = new vector<double>();


					L2->push_back((*color)[0]);
					L2->push_back((*color)[1]);
					L2->push_back((*color)[2]);

					vector<double> * tr_color = add(scale(L1, (1 - tr)), scale(L2, tr));
					final->push_back(round((*tr_color)[0]));
					final->push_back(round((*tr_color)[1]));
					final->push_back(round((*tr_color)[2]));
					return final;
				}
				else {
					vector<double> * L1 = new vector<double>();
					L1->push_back(r);
					L1->push_back(g);
					L1->push_back(b);
					vector<double> * tr_color = scale(L1, (1 - tr));
					final->push_back(round((*tr_color)[0]));
					final->push_back(round((*tr_color)[1]));
					final->push_back(round((*tr_color)[2]));
					return final;
				}
			}
			else {
				vector<double> * L1 = new vector<double>();
				L1->push_back(r);
				L1->push_back(g);
				L1->push_back(b);
				vector<double> * tr_color = scale(L1, (1 - tr));
				final->push_back(round((*tr_color)[0]));
				final->push_back(round((*tr_color)[1]));
				final->push_back(round((*tr_color)[2]));
				return final;
			}


		}
	}


	final->push_back(r);
	final->push_back(g);
	final->push_back(b);
	return final;
}

//void Renderer::prepare_raycast(const vector<Group *> models, const vector<Light * > & lights, const Material & materials) {
void Renderer::prepare_raycast(const vector<Face *> & faces, const vector<Elipse *> & elipses, const vector<Light * > & lights) {

	Vector3<double> * camPos = cam->getPos();
	Vector3<double> * fp = cam->getFocalPoint();

	Vector3<double> * u = cam->getHorizontalAxis();
	Vector3<double> * v = cam->getVerticalAxis();

	double min_y = frame->get_miny();
	double min_x = frame->get_minx();

	double max_y = frame->get_maxy();
	double max_x = frame->get_maxx();
	int depth = frame->get_depth();
	for (int grid_y = min_y; grid_y < max_y - 1; grid_y++) {
		for (int grid_x = min_x; grid_x < max_x - 1; grid_x++) {
			vector<double> pixel;// = new vector<double>();
			pixel.push_back((*camPos)[0] + ((*u)[0])*(grid_x)*(1 / abs(max_x)) + ((*v)[0])*(grid_y)*(1 / abs(max_y)));
			pixel.push_back((*camPos)[1] + (*u)[1] * grid_x*(1 / abs(max_x)) + (*v)[1] * grid_y*(1 / abs(max_y)));
			pixel.push_back((*camPos)[2] + (*u)[2] * grid_x*(1 / abs(max_x)) + (*v)[2] * grid_y*(1 / abs(max_y)));


			vector<int> * f_color;
			vector<int> * e_color;


			bool found_face = false;
			bool found_elipse = false;

			double f_dist;
			double e_dist;

			//faces
		/*	cout << "testing" << endl;
			for (int i = 0; i < faces.size(); i++) {
				cout << i << endl;
			}*/
			f_color = find_closest_face(fp, &pixel, faces, elipses, lights, depth, &f_dist, &found_face);
			//e_color = find_closest_elipse(fp, &pixel, faces, elipses, lights, depth, &e_dist, &found_elipse);

			//vector<int> * color;
		//	if (found_face && found_elipse) {
			//	if (f_dist < e_dist) {
					//color = f_color;
			//	}
			//	else {
			//		color = e_color;
			//	}

			//}
			//else if (found_face) {
			//	color = f_color;
			//}
			//else {
			//	color = e_color;
			//}

			if (found_face ) {//|| found_elipse) {
				//if (found_face) {
				int r = standardize((*f_color)[0]);
				int g = standardize((*f_color)[1]);
				int b = standardize((*f_color)[2]);
				fill(grid_x, grid_y, r, g, b);
				//color->clear();
				//color->~vector();
				// f_color->~vector();
				//   e_color->~vector();
			}
			delete(f_color);
		}
	}
	//cout << "test" << endl;
}

/*void Renderer::prepare_wireframe(vector<Group *> models) {

	vector<vector<double> *> P;
	vector<vector<double> *> R;
	vector<vector<double> *> T;

	vector<double> * n = normalize(vpn);

	vector<double> * u = normalize(cross_product(normalize(v_up), n));
	for (int i = 0; i<u->size(); i++) {
		if ((*u)[i] != (*u)[i]) {
			cerr << "Problem with camera: " << name << endl;
			exit(1);
		}
	}
	vector<double> * v = normalize(cross_product(n, u));

	//First we need to make three matrices, P, R, and T

	// P
	//
	double one[] = { 1, 0, 0, 0 };
	double two[] = { 0, 1, 0, 0 };
	double three[] = { 0, 0, 0, 0 };
	double four[] = { 0, 0, (1 / focal_length), 1 };
	//construct P using arrays
	P.push_back(new vector<double>(one, one + sizeof(one) / sizeof(double)));
	P.push_back(new vector<double>(two, two + sizeof(two) / sizeof(double)));
	P.push_back(new vector<double>(three, three + sizeof(three) / sizeof(double)));
	P.push_back(new vector<double>(four, four + sizeof(four) / sizeof(double)));

	// R
	//
	{
		double one[] = { (*u)[0], (*u)[1], (*u)[2], 0 };
		double two[] = { (*v)[0], (*v)[1], (*v)[2], 0 };
		double three[] = { (*n)[0], (*n)[1], (*n)[2], 0 };
		double four[] = { 0, 0, 0, 1 };
		//construct this using arrays
		R.push_back(new vector<double>(one, one + sizeof(one) / sizeof(double)));
		R.push_back(new vector<double>(two, two + sizeof(two) / sizeof(double)));
		R.push_back(new vector<double>(three, three + sizeof(three) / sizeof(double)));
		R.push_back(new vector<double>(four, four + sizeof(four) / sizeof(double)));
	}
	// T
	//
	{
		double one[] = { 1, 0, 0, -x };
		double two[] = { 0, 1, 0, -y };
		double three[] = { 0, 0, 1, -z };
		double four[] = { 0, 0, 0, 1 };
		//construct this using arrays
		T.push_back(new vector<double>(one, one + sizeof(one) / sizeof(double)));
		T.push_back(new vector<double>(two, two + sizeof(two) / sizeof(double)));
		T.push_back(new vector<double>(three, three + sizeof(three) / sizeof(double)));
		T.push_back(new vector<double>(four, four + sizeof(four) / sizeof(double)));
	}

	vector<vector<double> *> * final = multiply(&P, multiply(&R, &T));

	for (int i = 0; i < models.size(); i++) {
		models[i]->arbitrary(final);
	}

	vector<Vertex> * lines = new vector<Vertex>();
	for (int i = 0; i < models.size(); i++) {
		const vector<Vertex> * temp = models[i]->get_lines();
		for (int j = 0; j < temp->size(); j++) {
			lines->push_back((*temp)[j]);
		}
	}
	bresenham(clip(lines));
}*/

/*vector<Vertex> * Renderer::clip(vector<Vertex> * lines) {
	vector<Vertex> * results = new  vector<Vertex>();
	if (frames.size() == 0) {
		cerr << "No wire-frame included for camera: " << name << endl;
		exit(1);
	}
	Wireframe frame = frames[0];
	const int above = 1;
	const int below = 2;
	const int left = 4;
	const int right = 8;
	vector<int>  codes;
	for (int i = 0; i < lines->size(); i++) {

		codes.push_back(0);
		if ((*lines)[i].get_x() < frame.get_minx()) {//&& (abs(abs((*lines)[i].get_x()) - abs(frame.get_minx())) < .00001)) {
			codes[i] = codes[i] | left;
		}
		if ((*lines)[i].get_x() > frame.get_maxx()){// && (abs(abs((*lines)[i].get_x()) - abs(frame.get_maxx())) < .00001)) {
			codes[i] = codes[i] | right;
		}
		if ((*lines)[i].get_y() < frame.get_miny()) {// && (abs(abs((*lines)[i].get_y()) - abs(frame.get_miny())) < .00001)) {
			codes[i] = codes[i] | below;
		}
		if ((*lines)[i].get_y() > frame.get_maxy()) {// && (abs(abs((*lines)[i].get_y()) - abs(frame.get_maxy())) < .00001)) {
			codes[i] = codes[i] | above;
		}
		if ((i % 2) == 1) {
			if ((codes[i] | codes[i - 1]) == 0) {
				results->push_back((*lines)[i - 1]);
				results->push_back((*lines)[i]);
			}
			else if ((codes[i] & codes[i - 1]) != 0) {
			}
			else {
				//  cout << "line: " << endl;
				//cout << "x1:  " << (*lines)[i-1].get_x() << " y1: " << (*lines)[i-1].get_y() << endl;
				//cout << "x2:  " << (*lines)[i].get_x() << " y2: " << (*lines)[i].get_y() << endl;

				vector<Vertex> * next = new vector<Vertex>();
				for (int j = i - 1; j < i + 1; j++) {
					bool found = false;//start work here
					if (codes[j] == 0) {
						found = true;
						//Vertex temp = Vertex((*lines)[j]);
						//cout << "\t1a. " << (*lines)[j];
						//cout << "\t1. " << temp;
						next->push_back((*lines)[j]);
					}
					if ((codes[j] & left) == left && !found) {
						double c = frame.get_minx();

						double x1 = (*lines)[i - 1].get_x();
						double x2 = (*lines)[i].get_x();
						double y1 = (*lines)[i - 1].get_y();
						double y2 = (*lines)[i].get_y();
						double y;

						if (abs(x2) < .000001) {
							double m = (y2 - y1) / (x2 - x1);
							double b = y1 - m*(x1);
							y = m*c + b;
						}
						else {
							double t = (c - x1) / (x2 - x1);
							y = y1 + ((y2 - y1)*t);
						}
						if (y >= frame.get_miny() && y <= frame.get_maxy()) {

							Vertex temp = Vertex(c, y, 0, 1);
							found = true;
							//cout << "\t2. " << temp;
							next->push_back(temp);
						}
					}
					if ((codes[j] & above) == above && !found) {
						double c = frame.get_maxy() - 1;

						double t = (c - (*lines)[i - 1].get_y()) / ((*lines)[i].get_y() - (*lines)[i - 1].get_y());
						double x = (*lines)[i - 1].get_x() + (((*lines)[i].get_x() - (*lines)[i - 1].get_x())*t);
						if (x >= frame.get_minx() && x <= frame.get_maxx()) {
							Vertex temp = Vertex(x, c, 0, 1);
							found = true;
							//	cout << "\t3. " << temp;
							next->push_back(temp);
						}
					}
					if ((codes[j] & right) == right && !found) {
						double c = frame.get_maxx() - 1;
						double x1 = (*lines)[i - 1].get_x();
						double x2 = (*lines)[i].get_x();
						double y1 = (*lines)[i - 1].get_y();
						double y2 = (*lines)[i].get_y();
						double y;
						if (x2 == 0) {
							double m = (y2 - y1) / (x2 - x1);
							double b = y1 - m*(x1);
							y = m*c + b;
						}
						else {
							double t = ((c - x1) / (x2 - x1));
							y = y1 + ((y2 - y1)*t);

						}
						if (y >= frame.get_miny() && y <= frame.get_maxy()) {

							Vertex temp = Vertex(c, y, 0, 1);
							//		cout << "\t4. " << temp;
							found = true;
							next->push_back(temp);
						}
					}
					if ((codes[j] & below) == below && !found) {

						double c = frame.get_miny();
						double t = (c - (*lines)[i - 1].get_y()) / ((*lines)[i].get_y() - (*lines)[i - 1].get_y());
						double x = (*lines)[i - 1].get_x() + (((*lines)[i].get_x() - (*lines)[i - 1].get_x())*t);
						if (x >= frame.get_minx() && x <= frame.get_maxx()) {
							Vertex temp = Vertex(x, c, 0, 1);
							//	cout << "\t5. " << temp;
							found = true;
							next->push_back(temp);
						}
					}
				}
				//cout << "next" << endl;
				if (next->size() == 2) {
					//cout << "||||" << endl;
					for (int i = 0; i < next->size(); i++) {
						//		cout << '\t' << (*next)[i];
						results->push_back((*next)[i]);
					}
				}
			}
		}
	}
	return results;
}*/


/*void Renderer::bresenham(std::vector<Vertex> * lines) {
	if (lines->size() == 0) {
		cout << "no remaining lines" << endl;
		return;
	}
	int adjust_x = abs(frames[0].get_minx());
	int adjust_y = abs(frames[0].get_miny());
	vector<vector<int>> * bitmap = new  vector<vector<int>>();
	for (int i = 0; i < abs(frames[0].get_miny()) + frames[0].get_maxy(); i++) {
		vector<int> row;
		for (int j = 0; j < abs(frames[0].get_minx()) + frames[0].get_maxx(); j++) {
			row.push_back(0);
		}
		bitmap->push_back(row);
	}

	for (int i = 0; i < lines->size() - 1; i = i + 2) {

		int d;
		int x2 = round((*lines)[i + 1].get_x()) + adjust_x;
		int x1 = round((*lines)[i].get_x()) + adjust_x;
		int y2 = round((*lines)[i + 1].get_y()) + adjust_y;
		int y1 = round((*lines)[i].get_y()) + adjust_y;

		//cout << "bresenham" << endl;
		//cout << "x1: " << x1 << " y1: " << y1 << endl;
		//cout << "x2: " << x1 << " y2: " << y2 << endl;

		int dx = x2 - x1;
		int dy = y2 - y1;

		if (dx < 0) {
			swap(x1, x2);
			swap(y1, y2);
		}

		dx = x2 - x1;
		dy = y2 - y1;
		//int c = dx*y1-dy*x1;
		int x, y;
		x = x1;
		y = y1;

		(*bitmap)[y][x] = 1;

		//cout << "dy: " << dy << " dx: " << dx << endl;
		if (dy == 0) {
			(*bitmap)[y][x + 1] = 1;
			for (x = x1 + 2; x < x2; x++) {
				(*bitmap)[y][x] = 1;
			}
		}
		else if (abs(dy) <= abs(dx) && dy > 0){
			d = 2 * dy - dx;
			if (d > 0) {
				y += 1;
			}
			(*bitmap)[y][x + 1] = 1;
			for (x = x1 + 2; x <= x2; x++) {
				if (d < 0) {
					d = d + 2 * (dy);
				}
				else {
					d = d + 2 * (dy - dx);
					y += 1;
				}
				(*bitmap)[y][x] = 1;
			}
		}
		else if (dy < 0 && abs(dy) <= abs(dx)) {//(dy < dx && dy <= 0  && dx > 0 && abs(dy) < dx) {
			d = 2 * dy + dx;
			if (d < 0) {
				y -= 1;
			}
			(*bitmap)[y][x + 1] = 1;
			for (x = x1 + 2; x < x2; x++) {
				if (d > 0) {
					d = d + 2 * (dy);
				}
				else {
					d = d + 2 * (dy + dx);
					y -= 1;
				}
				(*bitmap)[y][x] = 1;
			}
		}
		else if (dy > 0) {

			swap(x1, y1);
			swap(x2, y2);

			dx = x2 - x1;
			dy = y2 - y1;

			if (x2 < x1) {
				swap(x1, x2);
				swap(y1, y2);
			}

			dx = x2 - x1;
			dy = y2 - y1;
			x = x1;
			y = y1;

			d = 2 * dy - dx;
			if (d > 0) {
				y += 1;
			}
			(*bitmap)[x + 1][y] = 1;
			for (x = x1 + 2; x <= x2; x++) {
				if (d < 0) {
					d = d + 2 * (dy);
				}
				else {
					d = d + 2 * (dy - dx);
					y += 1;
				}
				(*bitmap)[x][y] = 1;
			}
		}
		else {
			swap(x1, y1);
			swap(x2, y2);

			dx = x2 - x1;
			dy = y2 - y1;

			if (x2 < x1) {
				swap(x1, x2);
				swap(y1, y2);
			}

			dx = x2 - x1;
			dy = y2 - y1;
			//    cout << "dy: " << dy << endl;
			//  cout << "dx: " << dx << endl;
			x = x1;
			y = y1;

			d = 2 * dy + dx;
			if (d < 0) {
				y += -1;
			}
			(*bitmap)[x + 1][y] = 1;
			for (x = x1 + 2; x <= x2; x++) {
				if (d > 0) {
					d = d + 2 * (dy);
				}
				else {
					d = d + 2 * (dy + dx);
					y += -1;
				}
				(*bitmap)[x][y] = 1;
			}
		}
	}
	// image = bitmap;   
}*/

bool Renderer::hasFrame() {
	return has_frame;
}

ostream & Renderer::operator<<(std::ostream & out) {
	out << "P3 " << abs(frame->get_minx()) + frame->get_maxx() << " " << abs(frame->get_miny()) + frame->get_maxy() << " " << 256 << '\n';
	for (int i = image->size() - 1; i > -1; i--) {
		for (int j = 0; j < (*image)[0]->size(); j++) {
			out << (*(*image)[i])[j] << " ";
			// if ((*(*image)[i])[j] == 1) {
			//	out << 255 << " " << 255 << " " << 255 << " ";
			// }
			// else {
			//out << 0 << " " << 0 << " " << 0 << " ";
			//}
		}
		out << '\n';
	}
	return out;
}

ostream & operator<<(std::ostream & out, const Renderer & c) {
	out << "P3 " << abs(c.frame->get_minx()) + c.frame->get_maxx() << " " << abs(c.frame->get_miny()) + c.frame->get_maxy() << " " << 256 << '\n';
	for (int i = c.image->size() - 1; i > -1; i--) {
		for (int j = 0; j < (*c.image)[0]->size(); j++) {
			out << (*(*c.image)[i])[j] << " ";
		}
		out << '\n';
	}
	return out;
}
