#ifndef BOO_MATH_UTILS_H
#define BOO_MATH_UTILS_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include "boo_result.h"
#include "boo_utils.h"
namespace booldog
{	
	namespace utils
	{
		namespace math
		{
			namespace geometry
			{
				booinline bool is_rectangles_intersect( float x0 , float y0 , float right0 , float bottom0 , float x1 , float y1 
					, float right1 , float bottom1 )
				{
					if( bottom0 <= y1 || y0 >= bottom1 || right0 <= x1 || x0 >= right1 )
						return false;
					return true;
				};
				booinline bool is_point_belongs_to_segment( float x1 , float y1 , float x2 , float y2 , float x , float y 
					, ::booldog::uint8 precision )
				{
					x = ::booldog::utils::round( x , precision );
					x1 = ::booldog::utils::round( x1 , precision );
					x2 = ::booldog::utils::round( x2 , precision );
					y = ::booldog::utils::round( y , precision );
					y1 = ::booldog::utils::round( y1 , precision );
					y2 = ::booldog::utils::round( y2 , precision );
					if( x2 == x1 )
					{
						if( x2 == x )
						{
							if( ( y >= y1 && y <= y2 ) || ( y >= y2 && y <= y1 ) )
								return true;
						}
					}
					else if( y2 == y1 )
					{
						if( y2 == y )
						{
							if( ( x >= x1 && x <= x2 ) || ( x >= x2 && x <= x1 ) )
								return true;
						}
					}
					else
					{
						float left = .0f , right = .0f , top = .0f , bottom = .0f;
						float dx = x2 - x1;
						float dy = y2 - y1;
						float slope = dy / dx;
						float intercept = y1 - slope * x1;
						if( x1 < x2 )
						{
							left = x1;
							right = x2;
						}
						else
						{
							left = x2;
							right = x1;
						}
						if( y1 < y2 )
						{
							top = y1;
							bottom = y2;
						}
						else
						{
							top = y2;
							bottom = y1;
						}
						if( slope * x + intercept > ( y - 0.01 ) 
							&& slope * x + intercept < ( y + 0.01 ) )
						{
							if( x >= left && x <= right && 
								y >= top && y <= bottom )
								return true;
						}
					}
					return false;
				};
				booinline bool is_segments_intersect( float x1 , float y1 , float x2 , float y2 , float x3 , float y3 , float x4 
					, float y4 , float& x , float& y , bool check_belong_to_segments , ::booldog::uint8 precision )
				{
					x1 = ::booldog::utils::round( x1 , precision );
					x2 = ::booldog::utils::round( x2 , precision );
					x3 = ::booldog::utils::round( x3 , precision );
					x4 = ::booldog::utils::round( x4 , precision );
					y1 = ::booldog::utils::round( y1 , precision );
					y2 = ::booldog::utils::round( y2 , precision );
					y3 = ::booldog::utils::round( y3 , precision );
					y4 = ::booldog::utils::round( y4 , precision );
					float straight1_x = x2 - x1;
					float straight1_y = y2 - y1;
					float straight2_x = x4 - x3;
					float straight2_y = y4 - y3;
					float a1 = - straight1_y;
					float b1 = + straight1_x;
					float d1 = - ( a1 * x1 + b1 * y1 );
					float a2 = - straight2_y;
					float b2 = + straight2_x;
					float d2 = - ( a2 * x3 + b2 * y3 );
					float seg1_line2_start = a2 * x1 + b2 * y1 + d2;
					float seg1_line2_end = a2 * x2 + b2 * y2 + d2;
					float seg2_line1_start = a1 * x3 + b1 * y3 + d1;
					float seg2_line1_end = a1 * x4 + b1 * y4 + d1;
					if( seg1_line2_start * seg1_line2_end >= 0 || seg2_line1_start * seg2_line1_end >= 0 ) 
					{
						if( check_belong_to_segments )
						{
							if( ::booldog::utils::math::geometry::is_point_belongs_to_segment( x3 , y3 , x4 , y4 , x1 , y1 , precision ) )
							{
								if( x1 != x3 || y1 != y3 )
								{
									if( ::booldog::utils::math::geometry::is_point_belongs_to_segment( x2 , y2 , x3 , y3 , x1 , y1 , precision ) )
										return false;
								}
								else if( x1 != x4 || y1 != y4 )
								{
									if( ::booldog::utils::math::geometry::is_point_belongs_to_segment( x2 , y2 , x4 , y4 , x1 , y1 , precision ) )
										return false;
								}
								x = x1;
								y = y1;
								return true;
							}
							else if( ::booldog::utils::math::geometry::is_point_belongs_to_segment( x3 , y3 , x4 , y4 , x2 , y2 , precision ) )
							{
								if( x2 != x3 || y2 != y3 )
								{
									if( ::booldog::utils::math::geometry::is_point_belongs_to_segment( x1 , y1 , x3 , y3 , x2 , y2 , precision ) )
										return false;
								}
								else if( x2 != x4 || y2 != y4 )
								{
									if( ::booldog::utils::math::geometry::is_point_belongs_to_segment( x1 , y1 , x4 , y4 , x2 , y2 , precision ) )
										return false;
								}
								x = x2;
								y = y2;
								return 1;
							}
							else if( ::booldog::utils::math::geometry::is_point_belongs_to_segment( x1 , y1 , x2 , y2 ,  x3 , y3 , precision ) )
							{
								if( x3 != x1 || y3 != y1 )
								{
									if( ::booldog::utils::math::geometry::is_point_belongs_to_segment( x4 , y4 , x1 , y1 , x3 , y3 , precision ) )
										return false;
								}
								else if( x3 != x2 || y3 != y2 )
								{
									if( ::booldog::utils::math::geometry::is_point_belongs_to_segment( x4 , y4 , x2 , y2 , x3 , y3 , precision ) )
										return false;
								}
								x = x3;
								y = y3;
								return 1;
							}
							else if( ::booldog::utils::math::geometry::is_point_belongs_to_segment( x1 , y1 , x2 , y2 , x4 , y4 , precision ) )
							{
								if( x4 != x1 || y4 != y1 )
								{
									if( ::booldog::utils::math::geometry::is_point_belongs_to_segment( x3 , y3 , x1 , y1 , x4 , y4 , precision ) )
										return false;
								}
								else if( x4 != x2 || y4 != y2 )
								{
									if( ::booldog::utils::math::geometry::is_point_belongs_to_segment( x3 , y3 , x2 , y2 , x4 , y4 , precision ) )
										return false;
								}
								x = x4;
								y = y4;
								return true;
							}
						}
						return false;
					}
					float u = seg1_line2_start / ( seg1_line2_start - seg1_line2_end );
					x = ::booldog::utils::round( x1 + u * straight1_x , precision );
					y = ::booldog::utils::round( y1 + u * straight1_y , precision );
					return true;
				};
				booinline bool is_point_belongs_to_rectangle( float x0 , float y0 , float x1 , float y1 , float x2 , float y2 , float x3 
					, float y3 , float x , float y , ::booldog::uint8 precision )
				{
					x0 = ::booldog::utils::round( x0 , precision ); 
					x1 = ::booldog::utils::round( x1 , precision );
					x2 = ::booldog::utils::round( x2 , precision );
					x3 = ::booldog::utils::round( x3 , precision );
					x = ::booldog::utils::round( x , precision );
					y0 = ::booldog::utils::round( y0 , precision ); 
					y1 = ::booldog::utils::round( y1 , precision );
					y2 = ::booldog::utils::round( y2 , precision );
					y3 = ::booldog::utils::round( y3 , precision );
					y = ::booldog::utils::round( y , precision );
					float max_x = x0;
					float max_y = y0;
					float min_x = x0;
					float min_y = y0;
					if( x1 > max_x )
						max_x = x1;
					if( y1 > max_y )
						max_y = y1;
					if( x1 < min_x )
						min_x = x1;
					if( y1 < min_y )
						min_y = y1;
					if( x2 > max_x )
						max_x = x2;
					if( y2 > max_y )
						max_y = y2;
					if( x2 < min_x )
						min_x = x2;
					if( y2 < min_y )
						min_y = y2;
					if( x3 > max_x )
						max_x = x3;
					if( y3 > max_y )
						max_y = y3;
					if( x3 < min_x )
						min_x = x3;
					if( y3 < min_y )
						min_y = y3;
					if( x >= min_x && y >= min_y && x <= max_x && y <= max_y )
					{
						size_t intersection_count = 0;
						if( ::booldog::utils::math::geometry::is_segments_intersect( x , y , max_x + 64 , y , x0 , y0 , x1 , y1 , min_x , min_y , 0 , precision ) == 1 )
							intersection_count++;
						if( ::booldog::utils::math::geometry::is_segments_intersect( x , y , max_x + 64 , y , x1 , y1 , x2 , y2 , min_x , min_y , 0 , precision ) == 1 )
							intersection_count++;
						if( ::booldog::utils::math::geometry::is_segments_intersect( x , y , max_x + 64 , y , x2 , y2 , x3 , y3 , min_x , min_y , 0 , precision ) == 1 )
							intersection_count++;
						if( ::booldog::utils::math::geometry::is_segments_intersect( x , y , max_x + 64 , y , x3 , y3 , x0 , y0 , min_x , min_y , 0 , precision ) == 1 )
							intersection_count++;
						if( intersection_count > 0 )
						{
							if( ::booldog::utils::odd< size_t >( intersection_count ) )
								return true;
						}
					}
					return false;
				};
			};
			booinline int nextpowerof2( int number )
			{
				if( !( number & ( number - 1 ) ) )
					return number;
				while( number & ( number - 1 ) )
					number = number & ( number - 1 );
				number = number << 1;
				return number;
			};
		};
	};
};
#endif