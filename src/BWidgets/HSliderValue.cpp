/* HSliderValue.cpp
 * Copyright (C) 2018, 2019  Sven Jähnichen
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "HSliderValue.hpp"
#include "../BUtilities/to_string.hpp"

namespace BWidgets
{
HSliderValue::HSliderValue () :
	HSliderValue
	(
		0.0,
		0.0,
		BWIDGETS_DEFAULT_HSLIDERVALUE_WIDTH,
		BWIDGETS_DEFAULT_HSLIDERVALUE_HEIGHT,
		"hslidervalue",
		BWIDGETS_DEFAULT_VALUE,
		BWIDGETS_DEFAULT_RANGE_MIN,
		BWIDGETS_DEFAULT_RANGE_MAX,
		BWIDGETS_DEFAULT_RANGE_STEP,
		BWIDGETS_DEFAULT_VALUE_FORMAT
	)
{}

HSliderValue::HSliderValue (const double x, const double y, const double width, const double height, const std::string& name,
	const double value, const double min, const double max, const double step,
	const std::string& valueFormat) :
	HSlider (x, y, width, height, name, value, min, max, step),
	valueDisplay(0, 0, width, height / 2, name),
	valFormat (valueFormat), displayArea ()
{
	valueDisplay.setText (BUtilities::to_string (value, valueFormat));
	add (valueDisplay);
}

HSliderValue::HSliderValue (const HSliderValue& that) :
		HSlider (that), valueDisplay (that.valueDisplay), valFormat (that.valFormat),
		displayArea (that.displayArea)
{
	add (valueDisplay);
}

HSliderValue& HSliderValue::operator= (const HSliderValue& that)
{
	release (&valueDisplay);

	displayArea = that.displayArea;
	valFormat = that.valFormat;
	valueDisplay = that.valueDisplay;
	HSlider::operator= (that);

	add (valueDisplay);

	return *this;
}

Widget* HSliderValue::clone () const {return new HSliderValue (*this);}

void HSliderValue::setValue (const double val)
{
	HSlider::setValue (val);
	valueDisplay.setText(BUtilities::to_string (value, valFormat));
}

void HSliderValue::setValueFormat (const std::string& valueFormat) {valFormat = valueFormat;}
std::string HSliderValue::getValueFormat () const {return valFormat;}
Label* HSliderValue::getDisplayLabel () {return &valueDisplay;}

void HSliderValue::update ()
{
	HSlider::update ();

	// Update display
	valueDisplay.moveTo (displayArea.getPosition ());
	valueDisplay.resize (displayArea.getExtends ());
	if (valueDisplay.getFont ()->getFontSize () != displayArea.getHeight() * 0.8)
	{
		valueDisplay.getFont ()->setFontSize (displayArea.getHeight() * 0.8);
		valueDisplay.update ();
	}
	valueDisplay.setText (BUtilities::to_string (value, valFormat));
}

void HSliderValue::applyTheme (BStyles::Theme& theme) {applyTheme (theme, name_);}
void HSliderValue::applyTheme (BStyles::Theme& theme, const std::string& name)
{
	HSlider::applyTheme (theme, name);
	valueDisplay.applyTheme (theme, name);
}

void HSliderValue::updateCoords ()
{
	double w = getEffectiveWidth ();
	double h = getEffectiveHeight () / 2;

	knobRadius = (h < w / 2 ? h / 2 : w / 4);
	scaleArea = BUtilities::RectArea
	(
		getXOffset () + knobRadius,
		getYOffset () + h + knobRadius / 2,
		w - 2 * knobRadius,
		knobRadius
	);
	scaleXValue = scaleArea.getX() + getRelativeValue () * scaleArea.getWidth();

	knobPosition = BUtilities::Point (scaleXValue, scaleArea.getY() + scaleArea.getHeight() / 2);

	double dh = knobRadius * 2;
	double dw = 2.2 * dh;
	double dy = getYOffset () + h - dh;
	double dx = LIMIT (scaleXValue - dw / 2, getXOffset (), getXOffset () + getEffectiveWidth () - dw);
	displayArea = BUtilities::RectArea (dx, dy, dw, dh);
}

}
