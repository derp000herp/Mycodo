# coding=utf-8
import logging
from mycodo.databases.utils import session_scope

from mycodo.config import SQL_DATABASE_MYCODO

MYCODO_DB_PATH = 'sqlite:///' + SQL_DATABASE_MYCODO

logger = logging.getLogger("mycodo.database")


def db_retrieve_table(table, entry=None, device_id=None):
    """
    Return SQL database query object with optional filtering

    If entry='first', only the first table entry is returned.
    If entry='all', all table entries are returned.
    If device_id is set, the first entry with that device ID is returned.
    Otherwise, the table object is returned.
    """
    if device_id:
        return_table = table.query.filter(
            table.id == device_id)
    else:
        return_table = table.query

    if entry == 'first' or device_id:
        return_table = return_table.first()
    elif entry == 'all':
        return_table = return_table.all()

    return return_table


def db_retrieve_table_daemon(table, entry=None, device_id=None, unique_id=None):
    """
    Return SQL database query object with optional filtering
    If entry='first', only the first table entry is returned.
    If entry='all', all table entries are returned.
    If device_id is set, the first entry with that device ID is returned.
    Otherwise, the table object is returned.
    """
    logger.error("TEST05")
    try:
        with session_scope(MYCODO_DB_PATH) as new_session:
            logger.error("TEST06")

            if device_id:
                return_table = new_session.query(table).filter(
                    table.id == int(device_id))
            elif unique_id:
                return_table = new_session.query(table).filter(
                    table.unique_id == unique_id)
            else:
                logger.error("TEST07")
                return_table = new_session.query(table)

            logger.error("TEST08")

            if entry == 'first' or device_id or unique_id:
                logger.error("TEST09")
                return_table = return_table.first()
            elif entry == 'all':
                logger.error("TEST10")
                return_table = return_table.all()

            logger.error("TEST11")

            new_session.expunge_all()

            logger.error("TEST12")

            new_session.close()
    except Exception:
        logger.error("TEST13")
        logger.exception("TEST14")

    logger.error("TEST15")
    return return_table
