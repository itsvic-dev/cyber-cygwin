/*
 * Copyright (C) 2020 CyberOS.
 *
 * Author:     revenmartin <revenmartin@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "calcengine.h"
#include <QDebug>

CalcEngine::CalcEngine(QObject *parent)
    : QObject(parent),
      m_evaluator(new Evaluator)
{
}

QString CalcEngine::eval(const QString &expr)
{
    m_evaluator->setExpression(expr);
    m_evaluator->eval();

    if (m_evaluator->error().isEmpty()) {
        return QString(HMath::formatFixed(m_evaluator->eval()));
    } else {
        qDebug() << m_evaluator->error();
    }

    return "";
}
